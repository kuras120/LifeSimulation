#include <Human.hpp>
#include <iostream>
#include <Place.hpp>
#include <cstdlib>
#include <ctime>

Human::Human(std::vector<std::shared_ptr<Place>> places, std::string name, std::shared_ptr<spdlog::logger> logger) {
    Mutex = std::make_shared<std::mutex>();
    ConditionVariable = std::make_shared<std::condition_variable>();

    this->places = places;
    this->name_ = "human "  + name;
    this->logger_ = logger;
    position_ = std::pair<int, int>(12, 10);

    saturation_ = 100;
    fatigue_ = 100;
}

Human::Human(const std::string &name, const std::pair<int, int> &position_) : name_(name), position_(position_) {}

void Human::start()
{
    srand(time(NULL));
    int size = places.size();
    int random;
    do {
        logger_->info(name_ + " started work");
        if(saturation_ < 20) {
            places[0]->start(shared_from_this());
            fatigue_ -= rand() % 10 + 2;
            saturation_ = 100;
        }
        else if(fatigue_ < 20) {
            places[1]->start(shared_from_this());
            saturation_ -= rand() % 30 + 10;
            fatigue_ = 100;
        }

        else if(size >= 3){
            random = rand() % (size-2) + 2;
            logger_->info(random);
            places[random]->start(shared_from_this());
            fatigue_ -= rand() % 5 + 50;
            saturation_ -= rand() % 5 + 50;

        }
        else {
            goTo(10, 50);
            random = rand() % 2 + 0;
            if(random == 0) saturation_ = 0;
            else fatigue_ = 0;

            std::this_thread::sleep_for(std::chrono::seconds(5));
        }


    } while (isRunning_);
}

void Human::goTo(int x, int y) {
    int xInc = x>position_.first ? 1 : -1;
    int yInc = y>position_.second ? 1 : -1;

    while(y != position_.second)
    {
        position_.second+=yInc;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
    while(x != position_.first)
    {
        position_.first+=xInc;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
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
