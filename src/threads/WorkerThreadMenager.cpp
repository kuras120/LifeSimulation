//
// Created by root on 16.06.18.
//

#include "WorkerThreadMenager.h"
#include "../output/Logger.h"

WorkerThreadMenager::WorkerThreadMenager() {
    threadUpdateEmptyQueue.reset(
            new std::thread([this]
                            {
                                this->isRunning = true;
                                this->startThread();
                            })
            );
}

void WorkerThreadMenager::startThread() {
    std::unique_lock<std::mutex> lock(mutex);
    do
    {
        queueEmpty.wait(lock);

        while (isRunning && placesQueue.empty())
            placeInQueue.wait(lock);

        Logger::Instance()->Save("places queue size: " + std::to_string(placesQueue.size()));

        auto place = placesQueue.front();
        placesQueue.pop_front();

        auto tasks = place.getTasks();
        auto n = tasks.size();
        for (int i = 0; i < n; ++i) {
            auto task= tasks.front();
            tasks.pop_front();
            addTask(task);
        }

    } while (isRunning);
    queueEmpty.notify_all();
}

void WorkerThreadMenager::AddPlace(Place const& place) {

    std::lock_guard<std::mutex> mtx (mutex);
    placesQueue.push_back(place);
    placeInQueue.notify_one();
}

WorkerThreadMenager::~WorkerThreadMenager() {
    {
        isRunning = false;
        queueEmpty.notify_one();
    }
    threadUpdateEmptyQueue->join();
}
