

#ifndef LIFESIMULATION_BASKETBALL_H
#define LIFESIMULATION_BASKETBALL_H


#include "Place.hpp"

class Basketball : public Place{
    std::pair <int, int> location_ = std::make_pair(1, 30);
    std::pair <int, int> doors_ = std::make_pair(7, 33);
    std::shared_ptr<std::vector<std::shared_ptr<std::pair<int, int>>>> placesToPlay_;
    std::shared_ptr<std::vector<bool>> availability;
    std::shared_ptr<spdlog::logger> logger_;
    std::mutex mtx;
    std::mutex lock;
    std::condition_variable condition_variable;
    std::shared_ptr<int> counter;
    std::shared_ptr<std::pair<int, int>> score;
public:
    const std::shared_ptr<std::pair<int, int>> &getScore() const;

private:
    std::vector<std::shared_ptr<Human>> humans;
    void goToPlace(std::shared_ptr<Human> human);
    void startMatch();
    void match();

public:
    Basketball(std::shared_ptr<spdlog::logger> logger);

    std::pair<int, int> getLocation() override;
    std::shared_ptr<std::vector<std::shared_ptr<std::pair<int, int>>>> getPlacesToPlay();

    const std::list<std::function<void()>> &getTasks() override;

    void start(std::shared_ptr<Human> human) override;
};


#endif //LIFESIMULATION_BASKETBALL_H
