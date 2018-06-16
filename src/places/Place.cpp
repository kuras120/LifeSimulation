//
// Created by root on 16.06.18.
//

#include <iostream>
#include <chrono>
#include <thread>
#include "Place.h"
#include "../output/Logger.h"

void a0(){
    std::cout << "place0 task1\n";
    Logger::Instance()->Save("place0 task1");
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

void b0(){
    std::cout << "place0 task2\n";
    Logger::Instance()->Save("place0 task2");
    std::this_thread::sleep_for(std::chrono::seconds(1));
}
void c0(){
    std::cout << "place0 task3\n";
    Logger::Instance()->Save("place0 task3");
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

std::list<const std::function<void()>> Place::getTasks() {
    std::list<const std::function<void()>> tasks;
    tasks.push_back((const std::function<void()> &)a0);
    tasks.push_back((const std::function<void()> &)b0);
    tasks.push_back((const std::function<void()> &)c0);
    return tasks;
}
