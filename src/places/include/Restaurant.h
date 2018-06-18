//
// Created by wojtek on 17.06.18.
//

#ifndef LIFESIMULATION_RESTAURANT_H
#define LIFESIMULATION_RESTAURANT_H


#include <thread>
#include <vector>
#include <queue>
#include <condition_variable>
#include "Place.hpp"

struct table {
    std::shared_ptr<Human> human;
    bool mealReady;
    bool menuTaken;
    bool mealTaken;
    std::pair <int, int> location;
};

class Restaurant: public Place {
    std::pair <int, int> location_ = std::make_pair(16, 30);
    std::pair <int, int> doors_ = std::make_pair(16, 37);
private:
    void initializeTables();
    int freeTables;
    int tableCounter;
    std::condition_variable condition_variable_queue;
    std::shared_ptr<std::vector<std::shared_ptr<table>>> tables;
    std::shared_ptr<Human> waiter;
    std::shared_ptr<Human> cook;
    std::shared_ptr<std::queue<std::shared_ptr<table>>> tablesWaiter;
    std::shared_ptr<std::queue<std::shared_ptr<table>>> tablesCook;
    std::shared_ptr<std::queue<std::shared_ptr<Human>>> queue;

    std::thread waiterThread;
    std::thread cookThread;
    std::thread queueThread;
    bool open = true;
    std::shared_ptr<spdlog::logger> logger_;
    std::mutex humanLock;
    std::mutex queueLock;

private:
    void addHumanToQueue(std::shared_ptr<Human> human);
    std::shared_ptr<table> getFreeTable();
    void queueWorker();
    bool isRunning = true;
public:
    Restaurant(std::shared_ptr<spdlog::logger> logger);
    ~Restaurant();

    std::shared_ptr<Human> getWaiter();
    std::shared_ptr<std::vector<std::shared_ptr<table>>> getTables();
    void work(int worker);
    void start(std::shared_ptr<Human> human);
    std::pair <int, int> getLocation();
};


#endif //LIFESIMULATION_RESTAURANT_H
