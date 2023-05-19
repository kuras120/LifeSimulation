

#include "Basketball.hpp"

const std::list<std::function<void()>> &Basketball::getTasks() {
    return Place::getTasks();
}

void Basketball::start(std::shared_ptr<Human> human) {

    human->goTo(this->doors_.first+1, this->doors_.second);
    human->goTo(this->doors_.first-1, this->doors_.second);
    goToPlace(human);

    logger_->info(human->getName() + " idzie do wyjscia z boiska");
    human->setColor(WHITE);

    human->goTo(this->doors_.first-1, this->doors_.second);
    human->goTo(this->doors_.first+1, this->doors_.second);
}

std::pair<int, int> Basketball::getLocation() {
    return location_;
}



Basketball::Basketball(std::shared_ptr<spdlog::logger> logger) {
    logger_ = logger;
    playerReadyCounter_ = std::make_shared<int>(0);
    score_ = std::make_shared<std::pair<int, int>>(std::pair<int, int>(0,0));
    counter_ = std::make_shared<int>(0);
    playerReadyCounter_ = std::make_shared<int>(0);
    started_ = std::make_shared<bool>(false);

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

                while (*counter_ == 4)
                    conVarQueue_.wait(unique_lock);

                {
                    std::lock_guard<std::mutex> lockGuard(mtxAddPlayer);

                    mtxIncPlayerRdyCounter_.lock();
                    (*counter_)++;
                    mtxIncPlayerRdyCounter_.unlock();

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
                conVarQueue_.notify_one();
            }


            human->goToTarget();
            {
                std::unique_lock<std::mutex> unique_lock(*(human->Mutex));

                human->setColor(GREEN);
                mtxIncPlayerRdyCounter_.lock();

                if (*playerReadyCounter_ < 3) {
                    (*playerReadyCounter_)++;
                    mtxIncPlayerRdyCounter_.unlock();

                    while (!(*started_))
                        conVarPlayerReady.wait(unique_lock);
                    conVarPlayerReady.notify_one();

                    human->setColor(RED);
                    while ((*started_))
                        conVarPlayerReady.wait(unique_lock);
                    conVarPlayerReady.notify_one();

                } else {
                    (*playerReadyCounter_)++;

                    (*started_)=true;
                    conVarPlayerReady.notify_one();
                    mtxIncPlayerRdyCounter_.unlock();

                    human->setColor(RED);
                    logger_->info(human->getName() + " rozpoczyna mecz");
                    match();

                    conVarPlayerReady.notify_one();
                }


                conVarQueue_.notify_one();
            }
        }
    }
}

void Basketball::match() {
    logger_->info("mecz sie rozpoczal");
    *playerReadyCounter_=0;
    (*started_)=true;
    score_->first=0;
    score_->second=0;
    do{
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        if(time(0)%2) {
            score_->first++;
        } else
            score_->second++;
    } while (score_->first<5 && score_->second<4);
    logger_->info("mecz sie zakonczyl wynikiem: " + std::to_string(score_->first)+ ":" + std::to_string(score_->second));

    (*playerReadyCounter_)=0;
    (*counter_)=0;
    availability->at(0) = true;
    availability->at(1) = true;
    availability->at(2) = true;
    availability->at(3) = true;
    (*started_)=false;
}

const std::shared_ptr<std::pair<int, int>> &Basketball::getScore() const {
    return score_;
}

bool Basketball::isStarted_() const {
    return *started_;
}
