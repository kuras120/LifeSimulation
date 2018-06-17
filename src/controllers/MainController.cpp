#include <MainController.hpp>
#include <spdlog/spdlog.h>
#include <Restaurant.h>

MainController::MainController()
		: logger_(spdlog::basic_logger_mt("main", "dump.log"))
{
	logger_->debug(std::string(__FUNCTION__) + " have been initialised.");

	initialiseLoggers();
	initialisePlaces();
	initialiseConsole();
	initialiseHumans(1);
}

void MainController::initialiseLoggers()
{
	logger_->info("==================================================");
	logger_->info("=                  Initialized                   =");
	logger_->info("==================================================");
	logger_->flush_on(spdlog::level::info);
	logger_->set_level(spdlog::level::info);
}

MainController::~MainController()
{
	cleanUp();
	logger_->debug(std::string(__FUNCTION__) + " have been destroyed.");

	logger_->info("==================================================");
	logger_->info("=                  Finalised                     =");
	logger_->info("==================================================");
}

void MainController::initialiseHumans(unsigned humanCount)
{
    std::list<std::shared_ptr<Place>> places;

    std::shared_ptr<Place> restaurant = std::make_shared<Restaurant>();

    places.push_back(restaurant);

    int i = 0;
	logger_->info("Initialising new humans");
	while ( humanList_.size() != humanCount )
	{
		humanList_.emplace_back(places, "human " + i);
        i++;

	}
	logger_->info("Initialised " + std::to_string(humanList_.size()) + " humans");
}

void MainController::start() {
	startHumans();
	consoleThread_ = console_->SpawnThread();
}

void MainController::cleanUp()
{
	logger_->info("Waiting for threads to exit");
	console_->Stop();
	for ( auto& thread : humanThreadList_ )
	{
		thread.join();
	}
	consoleThread_.join();
	logger_->info("All threads stopped");
}

void MainController::startHumans()
{
	logger_->info("Creating threads");
	for ( auto& human : humanList_ )
	{
		humanThreadList_.emplace_back(
				&Human::start, human
				);
	}
	logger_->info("All threads ready");
}

void MainController::initialiseConsole() {
	console_= std::make_shared<Console>(this);
}

std::shared_ptr<Restaurant> &MainController::getRestaurant() {
	return restaurant_;
}

void MainController::initialisePlaces() {
	restaurant_= std::make_shared<Restaurant>();

	logger_->info("Initialised places");
}

std::shared_ptr<spdlog::logger> &MainController::getLogger() {
	return logger_;
}

std::list<Human> &MainController::getHumanList() {
	return humanList_;
}
