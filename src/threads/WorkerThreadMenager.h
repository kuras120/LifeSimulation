//
// Created by root on 16.06.18.
//

#ifndef LIFESIMULATION_WORKERTHREADMENAGER_H
#define LIFESIMULATION_WORKERTHREADMENAGER_H


#include "WorkerThread.hpp"
#include "../places/Place.hpp"

class WorkerThreadMenager : public WorkerThread {
    void AddPlaceAtFront(Place place);
    void AddPlaceAtBack(Place);

public:
    WorkerThreadMenager();
    ~WorkerThreadMenager();

    void AddPlace(const Place &place);
private:
    void startThread();
private:
    std::unique_ptr<std::thread> threadUpdateEmptyQueue;
    std::condition_variable placeInQueue;
    std::mutex mutex;
    std::list<Place> placesQueue;

};


#endif //LIFESIMULATION_WORKERTHREADMENAGER_H
