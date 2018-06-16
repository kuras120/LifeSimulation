//
// Created by root on 15.06.18.
//

#include "Logger.h"
#include <iostream>
#include <ctime>


Logger::Logger(std::string fileName) {
    logFile.open(fileName);

    if(!logFile.is_open()) {
        std::cout << "Logger err: unable to open " << fileName << "\n";
    }
}

bool Logger::Save(std::string text)
{
    std::lock_guard<std::mutex> l(mutex);
    logFile<< text << "\n";
    logFile.flush();
    return true;
}

std::shared_ptr<Logger> Logger::Instance() {
    static std::shared_ptr<Logger> instance;
    if (!instance)
    {
        //std::lock_guard<std::mutex> lock(Logger::mtx);

        if (!instance) {
            instance.reset(new Logger("../logger.txt"));
        }
    }
    return instance;
}

Logger::~Logger() {
    logFile.close();
}

