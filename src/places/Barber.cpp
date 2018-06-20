//
// Created by wojtek on 19.06.18.
//

#include "Barber.h"

Barber::Barber(std::shared_ptr<spdlog::logger> logger){
    this->logger_ = logger;
    occupiedSeats_ = 0;
    queueIn_ = std::make_shared<std::queue<std::shared_ptr<Human>>>();
    humansInQue_ = std::make_shared<std::list<std::shared_ptr<Human>>>();
    barber_ = std::make_shared<Human>("barber", std::pair<int,int>(8, 65));
    barber_->setColor(WHITE);
    barberThread_ = std::thread([this] {work();});
}
Barber::~Barber(){
    isRunning_ = false;
    barberThread_.join();
}
std::pair<int, int> Barber::getLocation() {
    return location_;
}

void Barber::start(std::shared_ptr<Human> human) {
    //logger_->info("hello boiz");
    human->goTo(12, 58);

    human->goTo(12, 61);

    int output = addToQue(human);

    if(output == 1) {
        std::unique_lock <std::mutex> lock(*(human->Mutex));
        human->setColor(YELLOW);
        logger_->info(human->getName() + " czeka na strzyzenie.");
        human->goToTarget();
        (human->ConditionVariable)->wait(lock);
        human->setTarget(human->getPossition().first, human->getPossition().second - 6);
        human->goToTarget();
        human->setColor(GREEN);

        mtxHumansInQue_.lock();
        humansInQue_->pop_front();
        for(auto temp: *humansInQue_) {
            temp->setTarget(temp->getPossition().first - 1, temp->getPossition().second);
            temp->goToTarget();
        }
        mtxHumansInQue_.unlock();
        human->setColor(RED);
        std::this_thread::sleep_for(std::chrono::seconds(5));

        human->setColor(WHITE);
        human->setTarget(human->getPossition().first + 4, human->getPossition().second);
        human->goToTarget();
        human->setTarget(human->getPossition().first, human->getPossition().second - 4);
        human->goToTarget();


        logger_->info(human->getName() + " zostal ostrzyzony.");
    }
}
void Barber::changePosition() {

}
int Barber::addToQue(std::shared_ptr<Human> human) {
    std::lock_guard<std::mutex> lock(mtxHumansInQue_);

    if(occupiedSeats_ < 5) {
        queueIn_->push(human);
        //human->goTo(13, 72);
        human->setTarget(human->getPossition().first - (4 - occupiedSeats_), human->getPossition().second + 13);
        //mtxHumansInQue_.lock();
        humansInQue_->push_back(human);
        //mtxHumansInQue_.unlock();
        mtxOccupiedSeats_.lock();
        occupiedSeats_++;
        mtxOccupiedSeats_.unlock();

        return 1;
    }
    return 0;

}
void Barber::work() {
    while(isRunning_){
        if(queueIn_->size() > 0) {
            logger_->info("Fryzjer strzyze klienta.");
            barber_->setColor(RED);
            auto human = queueIn_->front();
            std::this_thread::sleep_for(std::chrono::seconds(10));

            queueLock_.lock();
            queueIn_->pop();


            mtxOccupiedSeats_.lock();
            occupiedSeats_--;
            mtxOccupiedSeats_.unlock();
            queueLock_.unlock();

            //human = queueIn_->front();
            human->ConditionVariable->notify_one();
            barber_->setColor(WHITE);

        }
        else{
            logger_->info("Fryzjer spi.");
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    }
}

std::shared_ptr<Human> Barber::getBarber() {
    return barber_;
}