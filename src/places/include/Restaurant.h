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
    bool mealTaken;
};

class Restaurant: public Place {
    std::pair <int, int> location_ = std::make_pair(16, 30);
    std::pair <int, int> doors_ = std::make_pair(16, 37);
private:
    int freeTables;
    int tableCounter;
    std::queue<std::shared_ptr<table>> tables;
    std::thread waiter;
    std::thread cook;
    bool open = true;
    std::shared_ptr<spdlog::logger> logger_;

public:
    Restaurant(std::shared_ptr<spdlog::logger> logger);
    void work(int worker);
    void start(std::shared_ptr<Human> human);
    std::pair <int, int> getLocation();
};


#endif //LIFESIMULATION_RESTAURANT_H
