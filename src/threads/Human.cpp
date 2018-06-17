//
// Created by root on 16.06.18.
//

#include <Human.hpp>
#include <iostream>

Human::Human(std::list<std::shared_ptr<Place>> places, std::string name, std::shared_ptr<spdlog::logger> logger) {
    this->places = places;
    this->name = "human "  + name;
    this->logger_ = logger;
    position_ = std::pair<int, int>(12, 10);
}

void Human::start()
{
    logger_->info(name + " started work");
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

std::pair<int, int> Human::GetPossition() {
    return position_;
}
