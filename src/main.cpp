#include <iostream>
#include <unistd.h>
#include <thread>
#include "output/Logger.h"
#include "threads/WorkerThread.h"
#include "threads/WorkerThreadMenager.h"
#include "places/Place1.h"
#include "places/Place2.h"

Logger *logger;
WorkerThreadMenager thread;

void test() {
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

int main() {

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

    std::this_thread::sleep_for(std::chrono::milliseconds(3));
}