#include <thread>
#include <spdlog/spdlog.h>
#include <MainController.hpp>

int main() {
	MainController mainController;
	mainController.start();

	return EXIT_SUCCESS;
}