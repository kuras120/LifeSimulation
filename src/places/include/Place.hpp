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
    std::list<std::function<void()>> const& getTasks();

    virtual void start(std::shared_ptr<Human> human) = 0;
};
