//
// Created by wojtek on 17.06.18.
//

#include <iostream>
#include <mutex>
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
        if(worker == 0) {
            while (!tables.empty()) {
                table *t = tables.back();
                tables.pop();
                if (!t->menuTaken) {
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                    std::cout << "Menu przyniesione dla: " << t->humanNumber << std::endl;
                }
            }
        }
        else {
        }
    }
    while(!open){
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
void Restaurant::start() {
    std::mutex m;
    
    if(freeTables <= 0) m.lock();

    table *t;
    t->humanNumber = tableCounter - freeTables;
    t->menuTaken = false;
    t->mealReady = false;
    tables.push(t);

    freeTables --;

    while(!t->mealReady){

    }
    std::this_thread::sleep_for(std::chrono::seconds(2));

    if(freeTables <= 0) m.unlock();
    freeTables ++;


}
