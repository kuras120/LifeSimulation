//
// Created by oem on 6/17/18.
//

#include "include/Console.hpp"
#include "MainController.hpp"

Console::Console(MainController *controller) : controller(controller) {
    initializeWindow();
}

void Console::initializeWindow() {
    if((mainWin = initscr()) == NULL) {
        fprintf(stderr, "Error initialising ncurses.\n");
        exit(EXIT_FAILURE);
    }

    if(has_colors()==FALSE) {
        endwin();
        printf("colors not supported");
        exit(1);
    }

    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);

    initializePlaces();
    refresh();
}



Console::~Console() {
    std::this_thread::sleep_for(std::chrono::seconds(4));
    endwin();
}

void Console::initializePlaces() {
    attron(COLOR_PAIR(1));

    std::pair<int, int> restLoc = controller->getRestaurant()->getLocation();
    mvprintw(restLoc.first, restLoc.second, "####### ########");
    for (int i = 1; i < 7; ++i) {
        mvprintw(restLoc.first + i, restLoc.second, "#              #");
    }
    mvprintw(restLoc.first+7, restLoc.second, "################");

    refresh();
}

void Console::refreshWin() {



}


std::thread Console::SpawnThread() {
    isRunning = true;
    return std::thread([this] {this->run(); });
}

void Console::run() {
    while(!isRunning) {
        refreshWin();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

void Console::Stop() {
    isRunning = false;
}

