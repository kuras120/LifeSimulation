//
// Created by root on 16.06.18.
//

#include <iostream>
#include "Place.hpp"

std::list<std::function<void()>> const& Place::getTasks() {
    return tasks_;
}
