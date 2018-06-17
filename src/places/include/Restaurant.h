//
// Created by wojtek on 17.06.18.
//

#ifndef LIFESIMULATION_RESTAURANT_H
#define LIFESIMULATION_RESTAURANT_H


#include "Place.hpp"

class Restaurant: public Place {
    std::pair <int, int> location_ = std::make_pair(15, 30);
public:
    Restaurant();

    void start() override;
    std::pair <int, int> getLocation();
};


#endif //LIFESIMULATION_RESTAURANT_H
