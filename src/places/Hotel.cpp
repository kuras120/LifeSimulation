//
// Created by wojtek on 18.06.18.
//

#include "Hotel.h"

Hotel::Hotel(std::shared_ptr<spdlog::logger> logger){
    this->logger_ = logger;
}

std::pair<int, int> Hotel::getLocation() {
    return std::pair<int, int>(1, 1);
}

void Hotel::start(std::shared_ptr<Human> human) {
    human->goTo(10, 1);
    std::this_thread::sleep_for(std::chrono::seconds(2));
}
