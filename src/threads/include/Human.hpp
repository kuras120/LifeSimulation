//
// Created by root on 16.06.18.
//
#pragma once

#include <thread>
#include <Place.hpp>
#include "../IHuman.h"

class Human: public IHuman
{
private:
    std::string name;
	int saturation;
    int fatigue;
    bool alive = true;
    std::list<std::shared_ptr<Place>> places;
    std::pair<int, int> position_;

public:
    Human(std::list<std::shared_ptr<Place>> places, std::string name);

	void start();

	std::pair<int, int> GetPossition() override;

	int getSaturation() override;

    void setSaturation(int level) override;

    int getFatigue() override;

    void setFatigue(int level) override;
};
