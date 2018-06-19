//
// Created by wojtek on 19.06.18.
//

#include "Barber.h"

Barber::Barber(std::shared_ptr<spdlog::logger> logger){
    this->logger_ = logger;
    occupiedSeats_ = 0;
    queueIn_ = std::make_shared<std::queue<std::shared_ptr<Human>>>();
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
    logger_->info("hello boiz");
    human->goTo(10, 30);

    int output = addToQue(human);

    if(output == 1) {
        std::unique_lock <std::mutex> lock(*(human->Mutex));
        human->setColor(YELLOW);
        logger_->info(human->getName() + " czeka na strzyzenie.");
        (human->ConditionVariable)->wait(lock);
        logger_->info(human->getName() + " zostal ostrzyzony.");
    }
}

int Barber::addToQue(std::shared_ptr<Human> human) {
    std::lock_guard<std::mutex> lock(queueLock_);
    if(occupiedSeats_ < 5) {
        queueIn_->push(human);
        occupiedSeats_++;

        return 1;
    }
    return 0;

}
void Barber::work() {
    while(isRunning_){
        if(queueIn_->size() > 0) {
            logger_->info("Fryzjer strzyze klienta.");
            auto human = queueIn_->front();
            std::this_thread::sleep_for(std::chrono::seconds(10));

            queueLock_.lock();
            queueIn_->pop();
            occupiedSeats_ --;
            queueLock_.unlock();
            
            human->ConditionVariable->notify_one();

        }
        else{
            logger_->info("Fryzjer spi.");
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    }
}
