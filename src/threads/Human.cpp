#include <Human.hpp>
#include <iostream>
#include <Place.hpp>

Human::Human(std::list<std::shared_ptr<Place>> places, std::string name, std::shared_ptr<spdlog::logger> logger) {
    Mutex = std::make_shared<std::mutex>();
    ConditionVariable = std::make_shared<std::condition_variable>();
    this->places = places;
    this->name = "human "  + name;
    this->logger_ = logger;
    position_ = std::pair<int, int>(12, 10);
}

void Human::start()
{
    do {
        logger_->info(name + " started work");
        std::shared_ptr<Place> place = places.front();
        place->start(shared_from_this());
        places.pop_front();
        places.push_back(place);
        place = places.front();
        place->start(shared_from_this());
    } while (true);
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
    if(x==position_.first)
        xInc=0;
    int yInc = y>position_.second ? 1 : -1;
    if(y==position_.second)
        yInc=0;
    while(y != position_.second)
    {
        position_.second+=yInc;
        //logger_->info(name + " moved to " + std::to_string(position_.first) + "," + std::to_string(position_.second));
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
    while(x != position_.first)
    {
        position_.first+=xInc;
        //logger_->info(name + " moved to " + std::to_string(position_.first) + "," + std::to_string(position_.second));
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

std::string Human::GetName() {
    return name;
}

std::thread Human::SpawnThread() {
    return std::thread([this] {
        this->start(); });
}

Human::Human(const std::string &name, const std::pair<int, int> &position_) : name(name), position_(position_) {}

void Human::setTarger(int x, int y) {
    this->target_=std::pair<int,int>(x,y);
}

void Human::goToTarget() {
    GoTo(target_.first, target_.second);
}
