//
// Created by root on 6/20/18.
//

#ifndef LIFESIMULATION_CHESSCLUB_H
#define LIFESIMULATION_CHESSCLUB_H


#include "Place.hpp"

struct Table {
    std::mutex mtx;
    std::condition_variable conVar;
    std::pair<int, int> position;
    void start();
    bool available = true;
};

class ChessClub : public Place{
    std::pair <int, int> location_ = std::make_pair(1, 40);
    std::shared_ptr<spdlog::logger> logger_;
    std::shared_ptr<int> counter_;
    std::vector<std::shared_ptr<Table>> tables;
    std::mutex mtx_;
    std::mutex mtxQueue_;
    std::condition_variable conVar_;
    std::condition_variable conVarQueue_;

    std::shared_ptr<Table> lastTable = nullptr;
public:
    const std::vector<std::shared_ptr<Table>> &getTables() const;

private:
    void goToTable(std::shared_ptr<Human> human);
    bool isRunning = true;

public:
    ChessClub(const std::shared_ptr<spdlog::logger> &logger_);
    const std::pair<int, int> &getLocation_() const;

    std::pair<int, int> getLocation() override;

    void start(std::shared_ptr<Human> human) override;
};


#endif //LIFESIMULATION_CHESSCLUB_H
