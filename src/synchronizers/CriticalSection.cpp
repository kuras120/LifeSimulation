//
// Created by root on 15.06.18.
//

#include <pthread.h>
#include "CriticalSection.h"

void CriticalSection::Unlock() {
    pthread_mutex_unlock(&mtx);
}

void CriticalSection::Lock() {
    pthread_mutex_lock(&mtx);
}

CriticalSection::CriticalSection() {
    mtx = PTHREAD_MUTEX_INITIALIZER;
}
