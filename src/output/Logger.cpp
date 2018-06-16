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

    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];

    time (&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer,sizeof(buffer),"[%I:%M:%S] ",timeinfo);
    std::string str(buffer);

    logFile<< buffer <<text << "\n";
    logFile.flush();
    return true;
}

std::shared_ptr<Logger> Logger::Instance() {
    static std::shared_ptr<Logger> instance;
    if (!instance)
    {
        if (!instance) {
            instance.reset(new Logger("../logger.txt"));
        }
    }
    return instance;
}

Logger::~Logger() {
    logFile.close();
}

