#include <MainController.hpp>
#include <spdlog/spdlog.h>
#include <Restaurant.h>

MainController::MainController()
		: logger_(spdlog::basic_logger_mt("main", "dump.log"))
{

	logger_->debug(std::string(__FUNCTION__) + " have been initialised.");

	initialiseLoggers();
	initialisePlaces();
	initialiseHumans(58);
	initialiseConsole();

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
    int i = 0;
	logger_->info("Initialising new humans");
	humanList_ = std::make_shared<std::list<std::shared_ptr<Human>>>();
	while ( humanList_->size() != humanCount )
	{
		humanList_->emplace_back(
				std::make_shared<Human>(places, std::to_string(i), logger_));
		logger_->info(humanList_->back()->getName());
        i++;
	}
	logger_->info("Initialised " + std::to_string(humanList_->size()) + " humans");
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
	for ( auto& human : *humanList_ )
	{
		humanThreadList_.emplace_back(
                human->spawnThread()
				);
	}
	logger_->info("All threads ready");
}

void MainController::initialiseConsole() {
	console_= std::make_shared<Console>(std::shared_ptr<MainController>(this));
}

std::shared_ptr<Restaurant> &MainController::getRestaurant() {
	return restaurant_;
}

std::shared_ptr<Basketball> &MainController::getBasketball() {
	return basketball_;
}

std::shared_ptr<Barber> &MainController::getBarber() {
    return barber_;
}

void MainController::initialisePlaces() {
	restaurant_= std::make_shared<Restaurant>(logger_);
    basketball_ = std::make_shared<Basketball>(logger_);
	hotel_ = std::make_shared<Hotel>(logger_);
	barber_ = std::make_shared<Barber>(logger_);
	chessClub_ = std::make_shared<ChessClub>(logger_);

    places.push_back(restaurant_);
	places.push_back(hotel_);
	places.push_back(barber_);
    places.push_back(basketball_);
	//places.push_back(chessClub_);

	logger_->info("Initialised places");
}

std::shared_ptr<spdlog::logger> &MainController::getLogger() {
	return logger_;
}

std::shared_ptr<std::list<std::shared_ptr<Human>>> &MainController::getHumanList() {
	return humanList_;
}

const std::shared_ptr<ChessClub> &MainController::getChessClub_() const {
	return chessClub_;
}
