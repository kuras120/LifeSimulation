//
// Created by root on 16.06.18.
//

#include <Human.hpp>
#include <iostream>

Human::Human(std::list<std::shared_ptr<Place>> places, std::string name) {
    this->places = places;
    this->name = "human"  + name;
}

void Human::start()
{
    std::mutex m;
    for(int i = 0; i < 10; i++) {
        m.lock();
        std::cout << name << " " << i << std::endl;
        m.unlock();
    }

    std::shared_ptr<Place> place = places.front();
    place->start();
}

int Human::getSaturation() {
    return this->saturation;
}

void Human::setSaturation(int level) {
    this->saturation = level;
}

int Human::getFatigue() {
    return this->fatigue;
}

void Human::setFatigue(int level) {
    this->fatigue = level;
}
