//
// Created by oem on 6/18/18.
//

#include "Basketball.hpp"

const std::list<std::function<void()>> &Basketball::getTasks() {
    return Place::getTasks();
}

void Basketball::start(std::shared_ptr<Human> human) {

}

std::pair<int, int> Basketball::getLocation() {
    return location_;
}

Basketball::Basketball() {
    placesToPlay_ = std::make_shared<std::list<std::shared_ptr<std::pair<int, int>>>>();
    //std::make_shared(std::pair<int,int>());
    //placesToPlay_->emplace_back(std::make_shared(std::pair<int, int>(3, 4)));

}
