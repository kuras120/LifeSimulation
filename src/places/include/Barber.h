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
    std::pair <int, int> location_ = std::make_pair(7, 60);
    std::thread barberThread_;
    std::shared_ptr<spdlog::logger> logger_;
    std::shared_ptr<std::queue<std::shared_ptr<Human>>> queueIn_;
    std::shared_ptr<Human> barber_;
    std::shared_ptr<std::list<std::shared_ptr<Human>>> humansInQue_;
    bool isRunning_ = true;
    std::mutex queueLock_;
    std::mutex mtxOccupiedSeats_;
    std::mutex mtxHumansInQue_;
    int occupiedSeats_;

    int addToQue(std::shared_ptr<Human> human);
    void changePosition();
public:
    Barber(std::shared_ptr<spdlog::logger> logger);
    ~Barber();

    std::pair<int, int> getLocation() override;
    void work();
    void start(std::shared_ptr<Human> human) override;
    std::shared_ptr<Human> getBarber();
};


#endif //LIFESIMULATION_BARBER_H
