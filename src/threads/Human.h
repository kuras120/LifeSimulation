//
// Created by root on 16.06.18.
//

#ifndef LIFESIMULATION_HUMAN_H
#define LIFESIMULATION_HUMAN_H


#include <list>
#include "../places/Place.h"
#include "WorkerThread.h"

class Human : public WorkerThread{
public:
    Human();
    void AddPlaceAtFront(Place place);
    void AddPlaceAtBack(Place);
private:
    void popPlace();

private:
    std::unique_ptr<std::thread> threadUpdateEmptyQueue;
    std::mutex mutex;
    std::list<Place> placesQueue;
};


#endif //LIFESIMULATION_HUMAN_H
