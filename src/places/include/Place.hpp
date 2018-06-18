//
// Created by root on 16.06.18.
//
#pragma once

#include <functional>
#include <list>
#include <Human.hpp>

class Place {
    std::list<std::function<void()>> tasks_;
public:
    virtual std::list<std::function<void()>> const& getTasks();
    virtual std::pair <int, int> getLocation() = 0;
    virtual void start(std::shared_ptr<Human> human) = 0;
};
