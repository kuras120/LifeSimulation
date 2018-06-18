//
// Created by oem on 6/18/18.
//

#include "Basketball.hpp"

const std::list<std::function<void()>> &Basketball::getTasks() {
    return Place::getTasks();
}

void Basketball::start(std::shared_ptr<Human> human) {
    human->GoTo(this->doors_.first, this->doors_.second);
}

std::pair<int, int> Basketball::getLocation() {
    return location_;
}

Basketball::Basketball(std::shared_ptr<spdlog::logger> logger) {
    logger_ = logger;
    placesToPlay_ = std::make_shared<std::list<std::shared_ptr<std::pair<int, int>>>>();
    placesToPlay_->emplace_back(std::make_shared<std::pair<int,int>>(std::pair<int, int>(location_.first+2, location_.second+2)));
    placesToPlay_->emplace_back(std::make_shared<std::pair<int,int>>(std::pair<int, int>(location_.first+4, location_.second+2)));
    placesToPlay_->emplace_back(std::make_shared<std::pair<int,int>>(std::pair<int, int>(location_.first+2, location_.second+4)));
    placesToPlay_->emplace_back(std::make_shared<std::pair<int,int>>(std::pair<int, int>(location_.first+4, location_.second+4)));
    availability = std::make_shared<std::vector<bool>>();
    availability->emplace_back(true);
    availability->emplace_back(true);
    availability->emplace_back(true);
    availability->emplace_back(true);
}

std::shared_ptr<std::list<std::shared_ptr<std::pair<int, int>>>> Basketball::getPlacesToPlay() {
    return placesToPlay_;
}
