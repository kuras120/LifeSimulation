#include <MainController.hpp>
#include <spdlog/spdlog.h>

MainController::MainController()
		: logger_(spdlog::basic_logger_mt("main", "dump.log"))
{
	logger_->debug(std::string(__FUNCTION__) + " have been initialised.");

	initialiseLoggers();
	initialiseHumans(15);
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
	logger_->info("Initialising new humans");
	while ( humanList_.size() != humanCount )
	{
		humanList_.push_back({});
	}
	logger_->info("Initialised " + std::to_string(humanList_.size()) + " humans");
}

void MainController::start()
{
	startHumans();
}

void MainController::cleanUp()
{
	logger_->info("Waiting for threads to exit");
	for ( auto& thread : humanThreadList_ )
	{
		thread.join();
	}
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
