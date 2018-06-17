#include <thread>
#include <spdlog/spdlog.h>
#include <MainController.hpp>

int main() {
	std::shared_ptr<MainController> controller = std::make_shared<MainController>();
	controller->start();
	std::this_thread::sleep_for(std::chrono::milliseconds(20000));
	return EXIT_SUCCESS;
}