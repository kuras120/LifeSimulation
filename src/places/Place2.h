//
// Created by root on 16.06.18.
//

#ifndef LIFESIMULATION_PLACE2_H
#define LIFESIMULATION_PLACE2_H


#include "Place.h"

class Place2 : public Place{
public:
    std::list<const std::function<void()>> getTasks();
};


#endif //LIFESIMULATION_PLACE2_H
