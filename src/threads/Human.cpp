//
// Created by root on 16.06.18.
//

#include "Human.h"

void Human::AddPlaceAtFront(Place place) {
    std::lock_guard<std::mutex> mtx(mutex);
    placesQueue.push_front(place);
    itemInQueue.notify_one();
}

void Human::AddPlaceAtBack(Place) {

}

Human::Human() {
    threadUpdateEmptyQueue.reset(
            new std::thread([this]
                            {
                                std::unique_lock<std::mutex> unique_lock (WorkerThread::mutex);
                                this->isRunning = true;
                                do {
                                    queueEmpty.wait(unique_lock);
                                    //this->popPlace();
                                } while (this->isRunning);
                            }));

}
