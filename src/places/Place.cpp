
#include "Place.hpp"

#include <list>
#include <functional>


std::list<std::function<void()>> const& Place::getTasks() {
    return tasks_;
}
