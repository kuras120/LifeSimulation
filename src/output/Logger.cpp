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

Logger::~Logger() {
    logFile.close();
}

bool Logger::Save(std::string text)
{
    std::lock_guard<std::mutex> l(mtx);
    logFile<< text << "\n";
    logFile.flush();
    return true;
}
