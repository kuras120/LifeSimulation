

#include "Basketball.hpp"

const std::list<std::function<void()>> &Basketball::getTasks() {
    return Place::getTasks();
}

void Basketball::start(std::shared_ptr<Human> human) {

    human->goTo(this->doors_.first+1, this->doors_.second);
    human->goTo(this->doors_.first-1, this->doors_.second);
    goToPlace(human);

    logger_->info(human->getName() + " idzie do wyjscia z boiska");

    human->goTo(this->doors_.first-1, this->doors_.second);
    human->goTo(this->doors_.first+1, this->doors_.second);
}

std::pair<int, int> Basketball::getLocation() {
    return location_;
}



Basketball::Basketball(std::shared_ptr<spdlog::logger> logger) {
    logger_ = logger;
    score_ = std::make_shared<std::pair<int, int>>(std::pair<int, int>(0,0));
    counter_ = std::make_shared<int>(0);
    playerCounter_ = std::make_shared<int>(0);

    placesToPlay_ = std::make_shared<std::vector<std::shared_ptr<std::pair<int, int>>>>();
    placesToPlay_->push_back(std::make_shared<std::pair<int,int>>(std::pair<int, int>(location_.first+2, location_.second+2)));
    placesToPlay_->push_back(std::make_shared<std::pair<int,int>>(std::pair<int, int>(location_.first+4, location_.second+2)));
    placesToPlay_->push_back(std::make_shared<std::pair<int,int>>(std::pair<int, int>(location_.first+2, location_.second+4)));
    placesToPlay_->push_back(std::make_shared<std::pair<int,int>>(std::pair<int, int>(location_.first+4, location_.second+4)));

    availability = std::make_shared<std::vector<bool>>();
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
        {
            {
                std::unique_lock<std::mutex> unique_lock(mtx_);

                while (*counter_ == 4) conditionVariableQueue_.wait(unique_lock);

                {

                    std::lock_guard<std::mutex> lockGuard(selectPlaceMtx_);
                    (*counter_)++;

                    if (availability->at(0)) {
                        human->setTarget(placesToPlay_->at(0)->first, placesToPlay_->at(0)->second);
                        logger_->info(human->getName() + " wchodzi na pozycje nr 0");
                        availability->at(0) = false;
                    } else if (availability->at(1)) {
                        human->setTarget(placesToPlay_->at(1)->first, placesToPlay_->at(1)->second);
                        logger_->info(human->getName() + " wchodzi na pozycje nr 1");
                        availability->at(1) = false;
                    } else if (availability->at(2)) {
                        human->setTarget(placesToPlay_->at(2)->first, placesToPlay_->at(2)->second);
                        logger_->info(human->getName() + " wchodzi na pozycje nr 2");
                        availability->at(2) = false;
                    } else if (availability->at(3)) {
                        human->setTarget(placesToPlay_->at(3)->first, placesToPlay_->at(3)->second);
                        logger_->info(human->getName() + " wchodzi na pozycje nr 3");
                        availability->at(3) = false;
                    }
                }
                conditionVariableQueue_.notify_one();
            }


            human->goToTarget();
            {
                std::unique_lock<std::mutex> unique_lock(mtx_);

                human->setColor(GREEN);
                conditionVariableMatch_.notify_all();
                while (*counter_ != 4)
                    conditionVariableMatch_.wait(unique_lock);
                {
                    waitForPlayersMtx_.lock();
                    (*playerCounter_)++;

                    if(*playerCounter_==4){
                        waitForPlayersMtx_.unlock();
                        human->setColor(RED);
                        match();
                        human->setColor(WHITE);
                    } else {
                        waitForPlayersMtx_.unlock();

                        while ((*playerCounter_ )!=0)
                            conditionVariableMatch_.wait(unique_lock);
                        human->setColor(RED);
                        conditionVariableMatch_.wait(unique_lock);
                        human->setColor(WHITE);

                    }
                }
                conditionVariableQueue_.notify_one();
            }
        }
    }
}

void Basketball::match() {
    logger_->info("mecz sie rozpoczal");
    *playerCounter_=0;
    started_=true;
    conditionVariableMatch_.notify_all();
    conditionVariableMatch_.notify_all();

    conditionVariableMatch_.notify_all();
    conditionVariableMatch_.notify_all();
    do{
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        if(time(0)%2) {
            score_->first++;
        } else
            score_->second++;
    } while (score_->first<5 && score_->second<4);
    conditionVariableMatch_.notify_all();
    logger_->info("mecz sie zakonczyl wynikiem: " + std::to_string(score_->first)+ ":" + std::to_string(score_->second));
    score_->first=0;
    score_->second=0;

    (*counter_)=0;
    availability->at(0) = true;
    availability->at(1) = true;
    availability->at(2) = true;
    availability->at(3) = true;
    started_=false;
}

const std::shared_ptr<std::pair<int, int>> &Basketball::getScore() const {
    return score_;
}

bool Basketball::isStarted_() const {
    return started_;
}
