//
// Created by root on 15.06.18.
//

#ifndef LIFESIMULATION_CRITICALSECTION_H
#define LIFESIMULATION_CRITICALSECTION_H


#include <sys/types.h>

class CriticalSection {
    pthread_mutex_t mtx;

    public:
    CriticalSection();

    void Lock();
    void Unlock();
};


#endif //LIFESIMULATION_CRITICALSECTION_H
