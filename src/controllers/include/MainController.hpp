#pragma once

#include <memory>
#include <list>

#include <spdlog/logger.h>
#include <Human.hpp>
#include <Restaurant.h>
#include "../../console/include/Console.hpp"

class MainController
		: public std::enable_shared_from_this<MainController>
{
	//places
	std::shared_ptr<Restaurant> restaurant_;
public:
	std::shared_ptr<Restaurant> &getRestaurant();
	std::shared_ptr<spdlog::logger> &getLogger();
	std::shared_ptr<std::list<std::shared_ptr<Human>>> &getHumanList();

private:

	std::shared_ptr<spdlog::logger> logger_;
	std::shared_ptr<Console> console_;

	std::shared_ptr<std::list<std::shared_ptr<Human>>> humanList_;
	std::vector<std::thread> humanThreadList_;
	std::thread consoleThread_;
public:
    MainController();
    ~MainController();

    void start();

private:
    void initialiseLoggers();
    void initialiseHumans(unsigned humanCount);
    void initialisePlaces();
    void initialiseConsole();
    void startHumans();
    void cleanUp();
};
