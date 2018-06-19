#include <Human.hpp>
#include <iostream>
#include <Place.hpp>

Human::Human(std::list<std::shared_ptr<Place>> places, std::string name, std::shared_ptr<spdlog::logger> logger) {
    Mutex = std::make_shared<std::mutex>();
    ConditionVariable = std::make_shared<std::condition_variable>();

    this->places = places;
    this->name_ = "human "  + name;
    this->logger_ = logger;
    position_ = std::pair<int, int>(12, 10);
}

Human::Human(const std::string &name, const std::pair<int, int> &position_) : name_(name), position_(position_) {}

void Human::start()
{
    do {
        logger_->info(name_ + " started work");
        std::shared_ptr<Place> place = places.front();
        place->start(shared_from_this());
        places.pop_front();
        places.push_back(place);
        place = places.front();
        place->start(shared_from_this());
    } while (isRunning_);
}

void Human::goTo(int x, int y) {
    int xInc = x>position_.first ? 1 : -1;
    int yInc = y>position_.second ? 1 : -1;

    while(y != position_.second)
    {
        position_.second+=yInc;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    while(x != position_.first)
    {
        position_.first+=xInc;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

}

std::thread Human::spawnThread() {
    return std::thread([this] {
        this->start(); });
}

int Human::getSaturation() {
    return this->saturation_;
}

void Human::setSaturation(int level) {
    this->saturation_ = level;
}

int Human::getFatigue() {
    return this->fatigue_;
}

void Human::setFatigue(int level) {
    this->fatigue_ = level;
}

std::pair<int, int> Human::getPossition() {
    return position_;
}

void Human::setTarget(int x, int y) {
    this->target_=std::pair<int,int>(x,y);
}

void Human::goToTarget() {
    goTo(target_.first, target_.second);
}

void Human::stop() {
    isRunning_= false;
}

std::string Human::getName() {
    return name_;
}

Color Human::getColor() {
    return color_;
}

void Human::setColor(Color color) {
    color_=color;
}
