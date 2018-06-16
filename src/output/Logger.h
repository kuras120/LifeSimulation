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
#include <atomic>
#include <memory>

class Logger {
private:
    Logger(std::string fileName);

    static std::mutex mtx;
    std::mutex mutex;
    std::ofstream logFile;
public:
    ~Logger();
    static std::shared_ptr<Logger> Instance();
    bool Save(std::string text);
};


#endif //LIFESIMULATION_LOGGER_H
