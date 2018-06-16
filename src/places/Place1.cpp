//
// Created by root on 16.06.18.
//

#include <iostream>
#include "Place1.h"


void a1(){
    std::cout << "place1 some task 1\n";
}

void b1(){
    std::cout << "place1 some task 2\n";
}
void c1(){
    std::cout << "place1 some task 3\n";
}

std::list<const std::function<void()>> Place1::getTasks() {
    std::list<const std::function<void()>> tasks;
    tasks.push_back((const std::function<void()> &)a1);
    tasks.push_back((const std::function<void()> &)b1);
    return tasks;
}