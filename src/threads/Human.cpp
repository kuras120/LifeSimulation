//
// Created by root on 16.06.18.
//

#include <Human.hpp>
#include <iostream>

Human::Human(std::list<std::shared_ptr<Place>> places, std::string name) {
    this->places = places;
    this->name = name;
    position_ = std::pair<int, int>(12, 10);
}

void Human::start()
{
    for(int i = 0; i < 10; i++) {
        std::cout << name << " " << i;
    }
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

std::pair<int, int> Human::GetPossition() {
    return position_;
}
