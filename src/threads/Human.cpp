//
// Created by root on 16.06.18.
//

#include <Human.hpp>
#include <iostream>
#include <Place.hpp>

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
    place->start(this);
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

void Human::GoTo(int x, int y) {
    int xInc = x>position_.first ? 1 : -1;
    while(x != position_.first)
    {
        position_.first+=xInc;
        logger_->info(name + " moved to " + std::to_string(position_.first) + "," + std::to_string(position_.second));
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
    int yInc = y>position_.first ? 1 : -1;
    while(y != position_.second)
    {
        position_.second+=yInc;
        logger_->info(name + " moved to " + std::to_string(position_.first) + "," + std::to_string(position_.second));
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}
