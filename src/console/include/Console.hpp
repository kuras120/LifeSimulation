

#ifndef LIFESIMULATION_CONSOLE_H
#define LIFESIMULATION_CONSOLE_H


#include <memory>
#include <ncurses.h>
#include <thread>
#include <list>

class MainController;

class Console {

public:
    Console(std::shared_ptr<MainController> controller);
    ~Console();
    std::thread SpawnThread();
    void Stop();

private:
    void initializeWindow();
    void initializePlaces();
    void refreshWin();
    void run();

    std::list<std::pair<int, int>> toClear;
    bool basketballRefresh_ = false;
    bool isRunning;
    WINDOW * mainWin;
    std::shared_ptr<MainController> controller_;
};


#endif //LIFESIMULATION_CONSOLE_H
