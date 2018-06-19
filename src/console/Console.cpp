
#include "include/Console.hpp"
#include "MainController.hpp"

Console::Console(std::shared_ptr<MainController> controller) {
    controller_ = controller;
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
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_YELLOW, COLOR_BLACK);
    init_pair(6, COLOR_BLACK, COLOR_BLACK);

    initializePlaces();
    refresh();

    controller_->getLogger()->info("Initialised console");
}

Console::~Console() {
    endwin();
}

void Console::initializePlaces() {
    attron(COLOR_PAIR(2));

    std::pair<int, int> restLoc = controller_->getRestaurant()->getLocation();
    mvprintw(restLoc.first, restLoc.second, "#              #");
    for (int i = 1; i < 7; ++i) {
        mvprintw(restLoc.first + i, restLoc.second, "#              #");
    }
    mvprintw(restLoc.first+7, restLoc.second, "################");

    attron(COLOR_PAIR(4));
    for(auto table: *(controller_->getRestaurant()->getTables())){
        mvprintw(table->location.first, table->location.second, "O");
    }

    attron(COLOR_PAIR(2));
    restLoc = controller_->getBasketball()->getLocation();
    mvprintw(restLoc.first, restLoc.second, "#######");
    for (int i = 1; i < 6; ++i) {
        mvprintw(restLoc.first + i, restLoc.second, "#     #");
    }
    mvprintw(restLoc.first+6, restLoc.second, "### ###");

    //attron(COLOR_PAIR(4));
    //for(auto placeToPlay: *(controller_->getBasketball()->getPlacesToPlay())){
    //    mvprintw(placeToPlay->first, placeToPlay->second, "O");
    //}

    refresh();

}

void Console::refreshWin() {

    attron(COLOR_PAIR(6));
    for (auto poss: toClear) {
        mvprintw(poss.first, poss.second, " ");
    }

    if(controller_->getBasketball()->isStarted_()) {

        attron(COLOR_PAIR(1+basketballRefresh_));
        basketballRefresh_ =!basketballRefresh_;
        std::pair<int, int> restLoc = controller_->getBasketball()->getLocation();
        mvprintw(restLoc.first, restLoc.second, "#######");
        for (int i = 1; i < 6; ++i) {
            mvprintw(restLoc.first + i, restLoc.second, "#     #");
        }
        mvprintw(restLoc.first+6, restLoc.second, "### ###");
    }

    attron(COLOR_PAIR(1));
    (controller_->getBasketball()->getScore());

    std::string buff = std::to_string(controller_->getBasketball()->getScore()->first)+
            ":"+std::to_string(controller_->getBasketball()->getScore()->second);
        mvprintw((controller_->getBasketball()->getLocation().first -1),
                 (controller_->getBasketball()->getLocation().second + 2),
                buff.c_str());

    toClear.clear();
    for ( auto human : *(controller_->getHumanList()) )
    {
        std::pair<int, int> poss = human->getPossition();
        //controller_->getLogger()->info("poss: " + std::to_string(poss.first) + ", " + std::to_string(poss.second))
        attron(COLOR_PAIR(human->getColor()));
        toClear.push_back(poss);
        mvprintw(poss.first, poss.second, "H");
    }

    std::pair<int, int> poss = controller_->getRestaurant()->getWaiter()->getPossition();
    attron(COLOR_PAIR(controller_->getRestaurant()->getWaiter()->getColor()));
    toClear.push_back(poss);
    mvprintw(poss.first, poss.second, "W");
    move(1,1);
}


std::thread Console::SpawnThread() {

    return std::thread([this] {
        isRunning = true;
        this->run(); });
}

void Console::run() {
    while(isRunning) {
        refreshWin();
        refresh();
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

void Console::Stop() {
    isRunning = false;
}

