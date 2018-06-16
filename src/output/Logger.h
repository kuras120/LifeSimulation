//
// Created by root on 15.06.18.
//

#ifndef LIFESIMULATION_LOGGER_H
#define LIFESIMULATION_LOGGER_H


#include <string>
#include <fstream>
#include <mutex>
#include <atomic>
#include "../synchronizers/CriticalSection.h"

class Logger {
    std::ofstream logFile;
    CriticalSection criticalSection;
    ~Logger();
    std::mutex mtx;
public:
    Logger(std::string fileName);
    bool Save(std::string text);
};


#endif //LIFESIMULATION_LOGGER_H
