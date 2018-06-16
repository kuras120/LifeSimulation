//
// Created by root on 16.06.18.
//

#ifndef LIFESIMULATION_PLACE_H
#define LIFESIMULATION_PLACE_H


#include <functional>
#include <list>

class Place {
    std::list<std::function<void()>> tasks_;
public:
    std::list<std::function<void()>> const& getTasks();
};


#endif //LIFESIMULATION_PLACE_H
