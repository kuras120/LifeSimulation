//
// Created by root on 16.06.18.
//

#ifndef LIFESIMULATION_PLACE_H
#define LIFESIMULATION_PLACE_H


#include <functional>
#include <list>

class Place {
public:
    virtual std::list<const std::function<void()>> getTasks();
};


#endif //LIFESIMULATION_PLACE_H
