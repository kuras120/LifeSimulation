#include <iostream>
#include <unistd.h>
#include <thread>
#include "output/Logger.h"

void f(int i, Logger* logger){
    for(int j = 0; j<50; j++)
    {
        std::string buff = "text" + std::to_string(i) + " " + std::to_string(j);
        logger->Save(buff);
    }
}

int main() {
    Logger *logger = new Logger("../example.txt");
    logger->Save("sad");
    logger->Save("asd");
    logger->Save("ss");
    std::cout<<get_current_dir_name();

    int i = 3;
    std::thread t1(f, 1, logger);
    std::thread t2(f, 2, logger);
    std::thread t3(f, 3, logger);
    std::thread t4(f, 4, logger);
    std::thread t5(f, 5, logger);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();


    return 0;
}