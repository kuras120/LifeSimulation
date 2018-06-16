#pragma once

#include <memory>
#include <list>

#include <spdlog/logger.h>
#include <Human.hpp>

class MainController
{
	std::shared_ptr<spdlog::logger> logger_;

	std::list<Human> humanList_;
	std::vector<std::thread> humanThreadList_;
public:
    MainController();
    ~MainController();

    void start();

private:
    void initialiseLoggers();
    void initialiseHumans(unsigned humanCount);
    void startHumans();
    void cleanUp();
};
