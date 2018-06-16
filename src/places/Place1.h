//
// Created by root on 16.06.18.
//

#ifndef LIFESIMULATION_PLACE1_H
#define LIFESIMULATION_PLACE1_H


#include "Place.h"

class Place1 : public Place {
public:
    std::list<const std::function<void()>> getTasks() override;
};


#endif //LIFESIMULATION_PLACE1_H
