#include <iostream>
#include <unistd.h>
#include <thread>
#include "output/Logger.h"
#include "threads/WorkerThread.h"
#include "threads/WorkerThreadMenager.h"
#include "places/Place1.h"
#include "places/Place2.h"
#include <spdlog/spdlog.h>

Logger *logger;
WorkerThreadMenager thread;

int main() {

    spdlog::basic_logger_mt("main", "dump.log");
    spdlog::get("main")->info("Initialised");

    //Logger::Instance()
    //Logger::Instance()->Save("sad");
    //Logger::Instance()->Save("sad");
    //Logger::Instance()->Save("sad");
    std::cout<<"\n";
    Place place;
    Place1 place1;
    Place2 place2;
    //thread.AddPlace(place);
    //thread.AddPlace(place1);
   // thread.AddPlace(place);
    thread.AddPlace(place1);
    thread.AddPlace(place1);
    thread.AddPlace(place1);
    thread.AddPlace(place1);
    std::this_thread::sleep_for(std::chrono::seconds(1));

    //do
    //{
    //    std::cout << '\n' << "Press a key to continue...\n";
    //} while (std::cin.get() != '\n');


    return 0;
}