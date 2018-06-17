#include <thread>
#include <spdlog/spdlog.h>
#include <MainController.hpp>

int main() {
	MainController mainController;
	mainController.start();
	std::this_thread::sleep_for(std::chrono::milliseconds(20000));
	return EXIT_SUCCESS;
}