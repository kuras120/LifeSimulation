//
// Created by wojtek on 17.06.18.
//

#include <iostream>
#include <mutex>
#include <Human.hpp>
#include "Restaurant.h"

Restaurant::Restaurant() {
    tableCounter = 10;
    freeTables = 10;
    waiter = std::thread(std::bind(&Restaurant::work,this, 0));
    cook = std::thread(std::bind(&Restaurant::work,this, 1));
}
void Restaurant::work(int worker) {
    std::mutex m;
    while(open) {
        while (!tables.empty()) {
            auto t = tables.back();
            if(worker == 0) {
                if (!t->menuTaken) {
                    tables.pop();
                    t->menuTaken = true;
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                    std::cout << "Menu przyniesione dla: " << t->humanNumber << std::endl;
                    tables.push(t);
                }
                else if(t->mealReady) {
                    tables.pop();
                    t->mealTaken = true;
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                    std::cout << "Jedzenie przyniesione i zjedzone przez " << t->humanNumber << std::endl;
                }
            }
            else {
                if(t->menuTaken && !t->mealReady) {
                    tables.pop();
                    t->mealReady = true;
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                    std::cout << "Posilek zrobiony dla: " << t->humanNumber << std::endl;
                    tables.push(t);

                }
            }
        }
    }
    while(!open){
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
void Restaurant::start(std::shared_ptr<Human> human) {
    std::mutex m;
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
    while(!t->mealReady){

    }
    std::this_thread::sleep_for(std::chrono::seconds(2));

    freeTables ++;


}

std::pair<int, int> Restaurant::getLocation() {
    return location_;
}
