//
// Created by wojtek on 19.06.18.
//

#ifndef LIFESIMULATION_BARBER_H
#define LIFESIMULATION_BARBER_H


#include <spdlog/logger.h>
#include <Place.hpp>
#include <queue>

class Barber:public Place {
private:
    std::pair <int, int> location_ = std::make_pair(40, 30);
    std::thread barberThread_;
    std::shared_ptr<spdlog::logger> logger_;
    std::shared_ptr<std::queue<std::shared_ptr<Human>>> queueIn_;
    bool isRunning_ = true;
    std::mutex queueLock_;
    int occupiedSeats_;

    int addToQue(std::shared_ptr<Human> human);
public:
    Barber(std::shared_ptr<spdlog::logger> logger);
    ~Barber();

    std::pair<int, int> getLocation() override;
    void work();
    void start(std::shared_ptr<Human> human) override;
};


#endif //LIFESIMULATION_BARBER_H
