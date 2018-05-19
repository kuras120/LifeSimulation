CMAKE_MINIMUM_REQUIRED(VERSION 3.9)
SET(CMAKE_CXX_STANDARD 11)

PROJECT(LifeSimulation)

INCLUDE_DIRECTORIES("include")

ADD_EXECUTABLE(LifeSimulation
        src/main.cpp)

FIND_PACKAGE(Curses REQUIRED)
FIND_PACKAGE(Threads REQUIRED)

target_link_libraries(LifeSimulation ${CURSES_LIBRARIES})
target_link_libraries(LifeSimulation ${CMAKE_THREAD_LIBS_INIT})