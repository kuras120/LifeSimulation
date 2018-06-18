

#include "Basketball.hpp"

const std::list<std::function<void()>> &Basketball::getTasks() {
    return Place::getTasks();
}

void Basketball::start(std::shared_ptr<Human> human) {

    std::unique_lock<std::mutex> lock(*(human->Mutex));
    human->goTo(this->doors_.first, this->doors_.second);
    goToPlace(human);
    (human->ConditionVariable)->wait(lock);
    human->goToTarget();
    logger_->info(human->getName() + " wychodzi z boiska");
    human->goTo(doors_.first, doors_.second);
    human->start();
}

std::pair<int, int> Basketball::getLocation() {
    return location_;
}



Basketball::Basketball(std::shared_ptr<spdlog::logger> logger) {
    logger_ = logger;
    score = std::make_shared<std::pair<int, int>>(std::pair<int, int>(0,0));
    counter = std::make_shared<int>(0);
    placesToPlay_ = std::make_shared<std::vector<std::shared_ptr<std::pair<int, int>>>>();
    placesToPlay_->push_back(std::make_shared<std::pair<int,int>>(std::pair<int, int>(location_.first+2, location_.second+2)));
    placesToPlay_->push_back(std::make_shared<std::pair<int,int>>(std::pair<int, int>(location_.first+4, location_.second+2)));
    placesToPlay_->push_back(std::make_shared<std::pair<int,int>>(std::pair<int, int>(location_.first+2, location_.second+4)));
    placesToPlay_->push_back(std::make_shared<std::pair<int,int>>(std::pair<int, int>(location_.first+4, location_.second+4)));
    availability = std::make_shared<std::vector<bool>>();
    placesToPlay_->at(3);
    availability->push_back(true);
    availability->push_back(true);
    availability->push_back(true);
    availability->push_back(true);
}

std::shared_ptr<std::vector<std::shared_ptr<std::pair<int, int>>>> Basketball::getPlacesToPlay() {
    return placesToPlay_;
}

void Basketball::goToPlace(std::shared_ptr<Human> human) {
    {
        logger_->info(human->getName() + " wszedl na teren boiska");
        std::lock_guard<std::mutex> lock_guard(mtx);
        if(*counter == 4) {
            std::unique_lock<std::mutex> unique_lock(lock);
            condition_variable.wait(unique_lock);
        }
        (*counter)++;
        humans.push_back(human);
        if(availability->at(0)){
            human->setTarget(placesToPlay_->at(0)->first, placesToPlay_->at(0)->second);
            logger_->info(human->getName() + " wchodzi na pozycje "
                          + std::to_string(placesToPlay_->at(1)->first) + " "
                          + std::to_string(placesToPlay_->at(1)->second));
        } else if (availability->at(1)) {
            human->setTarget(placesToPlay_->at(1)->first, placesToPlay_->at(1)->second);
            logger_->info(human->getName() + " wchodzi na pozycje "
                          + std::to_string(placesToPlay_->at(2)->first) + " "
                          + std::to_string(placesToPlay_->at(2)->second));
        } else if (availability->at(2)) {
            human->setTarget(placesToPlay_->at(2)->first, placesToPlay_->at(2)->second);
            logger_->info(human->getName() + " wchodzi na pozycje "
                          + std::to_string(placesToPlay_->at(2)->first) + " "
                          + std::to_string(placesToPlay_->at(2)->second));
        } else if (availability->at(3)) {
            human->setTarget(placesToPlay_->at(3)->first, placesToPlay_->at(3)->second);
            logger_->info(human->getName() + " wchodzi na pozycje "
                          + std::to_string(placesToPlay_->at(3)->first) + " "
                          + std::to_string(placesToPlay_->at(3)->second));
        }


        human->ConditionVariable->notify_one();
        logger_->info(human->getName() + " wchodzi na pozycje "
                                         + std::to_string(placesToPlay_->at(0)->first) + " "
                                         + std::to_string(placesToPlay_->at(0)->second));
        if(*counter==4)
            startMatch();
    }
}

void Basketball::startMatch() {
    score->first = 0;
    score->second = 0;
    std::thread([this] {match();}).join();
}

void Basketball::match() {

    do{
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        if(time(0)%2) {
            score->first++;
        } else
            score->second++;
    } while (score->first<5 && score->second<5);
    humans.at(0)->ConditionVariable->notify_one();
    humans.at(1)->ConditionVariable->notify_one();
    humans.at(2)->ConditionVariable->notify_one();
    humans.at(3)->ConditionVariable->notify_one();
}

const std::shared_ptr<std::pair<int, int>> &Basketball::getScore() const {
    return score;
}
