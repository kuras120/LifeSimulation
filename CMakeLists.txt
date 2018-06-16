CMAKE_MINIMUM_REQUIRED(VERSION 3.9)
SET(CMAKE_CXX_STANDARD 11)

PROJECT(LifeSimulation)

INCLUDE_DIRECTORIES("include")

ADD_EXECUTABLE(LifeSimulation
        src/main.cpp src/output/Console.cpp src/output/Console.h src/output/Logger.cpp src/output/Logger.h src/synchronizers/CriticalSection.cpp src/synchronizers/CriticalSection.h src/threads/WorkerThread.cpp src/threads/WorkerThread.h src/threads/Human.cpp src/threads/Human.h src/places/Place.cpp src/places/Place.h src/threads/WorkerThreadMenager.cpp src/threads/WorkerThreadMenager.h src/places/Place1.cpp src/places/Place1.h src/places/Place2.cpp src/places/Place2.h)

FIND_PACKAGE(Curses REQUIRED)
FIND_PACKAGE(Threads REQUIRED)

target_link_libraries(LifeSimulation ${CURSES_LIBRARIES})
target_link_libraries(LifeSimulation ${CMAKE_THREAD_LIBS_INIT})