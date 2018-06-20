#include <thread>
#include <spdlog/spdlog.h>
#include <MainController.hpp>

int main() {
	MainController controller;
	controller.start();
	getch();
	//std::this_thread::sleep_for(std::chrono::milliseconds(400000));
	return EXIT_SUCCESS;
}