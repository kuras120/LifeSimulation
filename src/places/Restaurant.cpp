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
void Restaurant::work(int worker) {
    while(open) {
        while (!tables.empty()) {
            m.lock();
            auto t = tables.back();
            if(worker == 0) {
                if (!t->menuTaken) {
                    tables.pop();
                    t->menuTaken = true;
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                    std::string text = "Menu przyniesione dla: ";
                    text += std::to_string(t->humanNumber);
                    logger_->info(text);
                    //std::cout << "Menu przyniesione dla: " << t->humanNumber << std::endl;
                    tables.push(t);
                }
                else if(t->mealReady) {
                    tables.pop();
                    t->mealTaken = true;
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                    std::string text = "Jedzenie przyniesione i zjedzone przez ";
                    text += std::to_string(t->humanNumber);
                    logger_->info(text);
                    //std::cout << "Jedzenie przyniesione i zjedzone przez " << t->humanNumber << std::endl;
                }
            }
            else {
                if(t->menuTaken && !t->mealReady) {
                    tables.pop();
                    t->mealReady = true;
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                    std::string text = "Posilek zrobiony dla: ";
                    text += std::to_string(t->humanNumber);
                    logger_->info(text);
                    //std::cout << "Posilek zrobiony dla: " << t->humanNumber << std::endl;
                    tables.push(t);

                }
            }
            m.unlock();
        }
    }
    while(!open){
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
void Restaurant::start(std::shared_ptr<Human> human) {

    human->GoTo(doors_.first, doors_.second);

    m.lock();
    auto t = std::make_shared<table>();
    t->humanNumber = tableCounter - freeTables;
    t->menuTaken = false;
    t->mealReady = false;
    t->mealTaken = false;
    tables.push(t);

    freeTables --;
    m.unlock();

    while(!t->mealTaken){
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    freeTables ++;

}

std::pair<int, int> Restaurant::getLocation() {
    return location_;
}
