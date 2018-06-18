
#pragma once

#include <thread>
#include <mutex>
#include <spdlog/logger.h>
#include "../IHuman.h"
#include <list>
#include <condition_variable>

class Place;

enum Color {
    WHITE = 1,
    RED = 2,
    GREEN = 3,
    BLUE = 4,
    YELLOW = 5
};

class Human
		: public std::enable_shared_from_this<Human>,
		  public IHuman
{
private:
    std::string name_;
	int saturation_;
    int fatigue_;
    bool isRunning_ = true;
    std::list<std::shared_ptr<Place>> places;
    std::pair<int, int> position_;
    std::pair<int, int> target_;
	std::shared_ptr<spdlog::logger> logger_;
	Color color_ = WHITE;

public:
    Human(std::list<std::shared_ptr<Place>> places, std::string name, std::shared_ptr<spdlog::logger> logger);
    Human(const std::string &name, const std::pair<int, int> &position_);

    void goTo(int x, int y);
    void setTarget(int x, int y);
    void goToTarget();

    std::thread spawnThread();
    void start();
    void stop() override;

    std::string getName() override;
    std::pair<int, int> getPossition() override;
	int getSaturation() override;
    void setSaturation(int level) override;
    int getFatigue() override;
    void setFatigue(int level) override;
    Color getColor();
    void setColor(Color color);




    // To delete
    std::shared_ptr<std::mutex> Mutex;
    std::shared_ptr<std::condition_variable> ConditionVariable;
};
