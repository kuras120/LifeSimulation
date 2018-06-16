//
// Created by root on 16.06.18.
//

#include <iostream>
#include "Place.h"
void a0(){
    std::cout << "place0 some task 1\n";
}

void b0(){
    std::cout << "place0 some task 2\n";
}
void c0(){
    std::cout << "place0 some task 3\n";
}

std::list<const std::function<void()>> Place::getTasks() {
    std::list<const std::function<void()>> tasks;
    tasks.push_back((const std::function<void()> &)a0);
    tasks.push_back((const std::function<void()> &)b0);
    tasks.push_back((const std::function<void()> &)c0);
    return tasks;
}
