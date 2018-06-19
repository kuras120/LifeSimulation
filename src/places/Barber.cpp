//
// Created by wojtek on 19.06.18.
//

#include "Barber.h"

Barber::Barber(std::shared_ptr<spdlog::logger> logger){
    this->logger_ = logger;
    barberThread_ = std::thread([this] {work();});
    queSeatsThread_ = std::thread([this] {queWorker();});
    isRunning_ = true;
}
Barber::~Barber(){
    isRunning_ = false;
}
std::pair<int, int> Barber::getLocation() {
    return location_;
}

void Barber::start(std::shared_ptr<Human> human) {

}

void Barber::work() {
    while(isRunning_){

    }
}

void Barber::queWorker() {

}