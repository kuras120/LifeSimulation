//
// Created by wojtek on 17.06.18.
//

#ifndef LIFESIMULATION_RESTAURANT_H
#define LIFESIMULATION_RESTAURANT_H


#include <thread>
#include <vector>
#include <queue>
#include "Place.hpp"

struct table {
    int humanNumber;
    bool mealReady;
    bool menuTaken;
};

class Restaurant: public Place {
private:
    int freeTables;
    int tableCounter;
    std::queue<table*> tables;
    std::thread waiter;
    std::thread cook;
    bool open = true;

public:
    Restaurant();
    void work(int worker);
    void start() override;
};


#endif //LIFESIMULATION_RESTAURANT_H
