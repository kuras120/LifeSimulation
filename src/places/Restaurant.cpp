//
// Created by wojtek on 17.06.18.
//

#include <iostream>
#include <mutex>
#include <Human.hpp>
#include "Restaurant.h"

Restaurant::Restaurant(std::shared_ptr<spdlog::logger> logger) {
    tableCounter = 10;
    freeTables = 10;
    waiter = std::thread(std::bind(&Restaurant::work,this, 0));
    cook = std::thread(std::bind(&Restaurant::work,this, 1));
    this->logger_ = logger;
}
Restaurant::~Restaurant() {
    waiter.join();
    cook.join();
}
void Restaurant::work(int worker) {
    while(open) {
        while (!tables.empty()) {
            if(worker == 0) {
                auto t1 = tables.back();
                if (!t1->menuTaken) {
                    tables.pop();
                    t1->menuTaken = true;
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                    std::string text = "Menu przyniesione dla: ";
                    text += std::to_string(t1->humanNumber);
                    logger_->info(text);
                    //std::cout << "Menu przyniesione dla: " << t->humanNumber << std::endl;
                    tables.push(t1);
                }
                else if(t1->mealReady) {
                    tables.pop();
                    t1->mealTaken = true;
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                    std::string text = "Jedzenie przyniesione i zjedzone przez ";
                    text += std::to_string(t1->humanNumber);
                    logger_->info(text);
                    //std::cout << "Jedzenie przyniesione i zjedzone przez " << t->humanNumber << std::endl;
                    tables.push(t1);
                }
            }
            else if(worker == 1){
                auto t2 = tables.back();
                if(t2->menuTaken && !t2->mealReady) {
                    tables.pop();
                    t2->mealReady = true;
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                    std::string text = "Posilek zrobiony dla: ";
                    text += std::to_string(t2->humanNumber);
                    logger_->info(text);
                    //std::cout << "Posilek zrobiony dla: " << t->humanNumber << std::endl;
                    tables.push(t2);
                }
            }
        }
    }
    while(!open){
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
void Restaurant::start(std::shared_ptr<Human> human) {

    human->GoTo(doors_.first, doors_.second);
    humanLock.lock();
    auto t = std::make_shared<table>();
    t->humanNumber = tableCounter - freeTables;
    freeTables --;
    t->menuTaken = false;
    t->mealReady = false;
    t->mealTaken = false;
    tables.push(t);
    std::string text = "watek wszedl do restauracji ";
    text += std::to_string(t->humanNumber);
    logger_->info(text);

    humanLock.unlock();

    while(!t->mealTaken){
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    text = "watek wyszedl z restauracji.";
    text += std::to_string(t->humanNumber);
    logger_->info(text);
    freeTables ++;

}

std::pair<int, int> Restaurant::getLocation() {
    return location_;
}
