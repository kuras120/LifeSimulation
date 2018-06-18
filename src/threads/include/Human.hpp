//
// Created by root on 16.06.18.
//
#pragma once

#include <thread>
#include <mutex>
#include <spdlog/logger.h>
#include "../IHuman.h"
#include <list>

class Place;

class Human
		: public std::enable_shared_from_this<Human>,
		  public IHuman
{
private:
    std::string name;
	int saturation;
    int fatigue;
    bool alive = true;
    std::list<std::shared_ptr<Place>> places;
    std::pair<int, int> position_;
	std::shared_ptr<spdlog::logger> logger_;

public:
    Human(std::list<std::shared_ptr<Place>> places, std::string name, std::shared_ptr<spdlog::logger> logger);

    void GoTo(int x, int y);

    std::string GetName();

	void start();

	std::pair<int, int> GetPossition() override;

	int getSaturation() override;

    void setSaturation(int level) override;

    int getFatigue() override;

    void setFatigue(int level) override;
};
