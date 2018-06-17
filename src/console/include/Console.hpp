//
// Created by oem on 6/17/18.
//

#ifndef LIFESIMULATION_CONSOLE_H
#define LIFESIMULATION_CONSOLE_H


#include <memory>
#include <ncurses.h>
#include <thread>
#include <list>

class MainController;

class Console {

public:
    Console(MainController *controller);
    ~Console();
    std::thread SpawnThread();
    void Stop();

private:
    void initializeWindow();
    void initializePlaces();
    void refreshWin();
    void run();

    std::list<std::pair<int, int>> toClear;
    bool isRunning;
    WINDOW * mainWin;
    MainController *controller;
};


#endif //LIFESIMULATION_CONSOLE_H
