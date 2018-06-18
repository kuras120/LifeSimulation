

#include <iostream>
#include <mutex>
#include <Human.hpp>
#include "Restaurant.h"

Restaurant::Restaurant(std::shared_ptr<spdlog::logger> logger) {
    initializeTables();
    tablesWaiter = std::make_shared<std::queue<std::shared_ptr<table>>>();
    tablesCook = std::make_shared<std::queue<std::shared_ptr<table>>>();
    queue = std::make_shared<std::queue<std::shared_ptr<Human>>>();

    waiter = std::make_shared<Human>("waiter", std::pair<int,int>(doors_.first +5  ,doors_.second));

    waiterThread = std::thread([this] {work(0);});
    cookThread = std::thread([this] {work(1);});
    queueThread = std::thread([this] { queueWorker();});

    this->logger_ = logger;
}
Restaurant::~Restaurant() {
    isRunning = false;
    open = false;
    waiterThread.join();
    cookThread.join();
    queueThread.join();
}
void Restaurant::work(int worker) {
    while(isRunning) {
            if(worker == 0) {
                if (tablesWaiter->size() > 0) {
                    auto t1 = tablesWaiter->front();
                    if (!t1->menuTaken) {
                        tablesWaiter->pop();
                        waiter->goTo(t1->location.first + 1, t1->location.second + 1);
                        std::this_thread::sleep_for(std::chrono::milliseconds(500));
                        waiter->goTo(location_.first + 6, location_.second + 6);
                        t1->menuTaken = true;

                        std::string text = "Menu przyniesione dla: ";
                        text += (t1->human->getName());
                        logger_->info(text);
                        tablesCook->push(t1);

                    } else if (t1->mealReady) {
                        tablesWaiter->pop();
                        t1->mealTaken = true;
                        waiter->goTo(t1->location.first + 1, t1->location.second + 1);
                        std::this_thread::sleep_for(std::chrono::milliseconds(300));
                        std::string text = "Jedzenie przyniesione dla ";

                        text += (t1->human->getName());
                        logger_->info(text);
                        tablesCook->push(t1);
                        t1->human->ConditionVariable->notify_one();
                        t1->human = nullptr;
                        t1->mealTaken=false;
                        t1->menuTaken=false;
                        t1->mealReady=false;
                    } else if(t1->mealTaken) {
                        tablesWaiter->pop();
                        //t1->human->ConditionVariable->notify_one();
                        t1->human = nullptr;
                        t1->mealTaken=false;
                        t1->menuTaken=false;
                        t1->mealReady=false;
                    }
                }
            }
            else if(worker == 1){
                if(tablesCook->size()>0) {
                    auto t2 = tablesCook->front();
                    if (t2->menuTaken && !t2->mealReady) {
                        tablesCook->pop();
                        t2->mealReady = true;
                        std::this_thread::sleep_for(std::chrono::seconds(2));
                        std::string text = "Posilek zrobiony dla: ";
                        text += (t2->human->getName());
                        logger_->info(text);
                        tablesWaiter->push(t2);
                    }
                }
            }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    while(!open){
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
void Restaurant::start(std::shared_ptr<Human> human) {
    std::string text;

    human->goTo(doors_.first, doors_.second);
    human->setColor(RED);
    text =  human->getName() + " wszedl do restauracji";
    logger_->info(text);
    addHumanToQueue(human);

    std::unique_lock<std::mutex> lock(*(human->Mutex));
    human->setColor(YELLOW);
    (human->ConditionVariable)->wait(lock);
    text =  human->getName() + " idzie do stolika";
    human->goToTarget();
    (human->ConditionVariable)->wait(lock);

    text =  human->getName() + " je";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    text =  human->getName() + " idzie do wyjscia restauracji";
    human->goTo(doors_.first, doors_.second);
    human->setColor(WHITE);
}

std::pair<int, int> Restaurant::getLocation() {
    return location_;
}

void Restaurant::addHumanToQueue(std::shared_ptr<Human> human) {
    std::lock_guard<std::mutex> lock(queueLock);
    queue->push(human);
}

void Restaurant::queueWorker() {
    while (isRunning)
    {
        {
            std::lock_guard<std::mutex> lock(queueLock);
            if (queue->size() > 0) {
                auto freeTab = getFreeTable();
                if (freeTab != nullptr) {
                    auto human = queue->front();
                    freeTab->human = human;
                    tablesWaiter->push(freeTab);
                    queue->pop();
                    logger_->info(freeTab->human->getName() + " zajal stolik");
                    human->setTarget(freeTab->location.first - 1, freeTab->location.second - 1);
                    human->ConditionVariable->notify_one();
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

std::shared_ptr<table> Restaurant::getFreeTable() {
    for(auto tab: *tables) {
        if(tab->human== nullptr)
            return tab;
    }
    return nullptr;
}

std::shared_ptr<Human> Restaurant::getWaiter() {
    return waiter;
}

std::shared_ptr<std::vector<std::shared_ptr<table>>> Restaurant::getTables() {
    return tables;
}

void Restaurant::initializeTables() {
    tables = std::make_shared<std::vector<std::shared_ptr<table>>>();
    auto tab1 = std::make_shared<table>();
    tab1->mealReady=false;
    tab1->mealTaken=false;
    tab1->menuTaken=false;
    tab1->human= nullptr;
    tab1->location=std::pair<int,int>(location_.first+2, location_.second+2);
    tables->emplace_back(tab1);

    auto tab2 = std::make_shared<table>();
    tab2->mealReady=false;
    tab2->mealTaken=false;
    tab2->menuTaken=false;
    tab2->human=nullptr;
    tab2->location=std::pair<int,int>(location_.first+5, location_.second+2);
    tables->emplace_back(tab2);

    auto tab3 = std::make_shared<table>();
    tab3->mealReady=false;
    tab3->mealTaken=false;
    tab3->menuTaken=false;
    tab3->human= nullptr;
    tab3->location=std::pair<int,int>(location_.first+2, location_.second+5);
    tables->emplace_back(tab3);

    auto tab4 = std::make_shared<table>();
    tab4->mealReady=false;
    tab4->mealTaken=false;
    tab4->menuTaken=false;
    tab4->human= nullptr;
    tab4->location=std::pair<int,int>(location_.first+5, location_.second+5);
    tables->emplace_back(tab4);

    auto tab5 = std::make_shared<table>();
    tab5->mealReady=false;
    tab5->mealTaken=false;
    tab5->menuTaken=false;
    tab5->human= nullptr;
    tab5->location=std::pair<int,int>(location_.first+2, location_.second+8);
    tables->emplace_back(tab5);

    auto tab6 = std::make_shared<table>();
    tab6->mealReady=false;
    tab6->mealTaken=false;
    tab6->menuTaken=false;
    tab6->human= nullptr;
    tab6->location=std::pair<int,int>(location_.first+5, location_.second+8);
    tables->emplace_back(tab6);

    auto tab7 = std::make_shared<table>();
    tab7->mealReady=false;
    tab7->mealTaken=false;
    tab7->menuTaken=false;
    tab7->human= nullptr;
    tab7->location=std::pair<int,int>(location_.first+2, location_.second+11);
    tables->emplace_back(tab7);

    auto tab8 = std::make_shared<table>();
    tab8->mealReady=false;
    tab8->mealTaken=false;
    tab8->menuTaken=false;
    tab8->human= nullptr;
    tab8->location=std::pair<int,int>(location_.first+5, location_.second+11);
    tables->emplace_back(tab8);
}
