//
// Created by wojtek on 18.06.18.
//

#ifndef LIFESIMULATION_HOTEL_H
#define LIFESIMULATION_HOTEL_H


#include "Place.hpp"

class Hotel: public Place {

public:
    Hotel(std::shared_ptr<spdlog::logger> logger);
    std::shared_ptr<spdlog::logger> logger_;

    std::pair<int, int> getLocation() override;

    void start(std::shared_ptr<Human> human) override;
};


#endif //LIFESIMULATION_HOTEL_H
