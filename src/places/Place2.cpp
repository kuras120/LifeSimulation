//
// Created by root on 16.06.18.
//

#include <iostream>
#include "Place2.h"

void a(){
    std::cout << "place2 some task 1\n";
}

void b(){
    std::cout << "place2 some task 2\n";
}

std::list<const std::function<void()>> Place2::getTasks() {
    std::list<const std::function<void()>> tasks;
    tasks.push_back((const std::function<void()> &)a);
    tasks.push_back((const std::function<void()> &)b);
    return tasks;
}