CMAKE_MINIMUM_REQUIRED(VERSION 3.5.1)
SET(CMAKE_CXX_STANDARD 11)

PROJECT(LifeSimulation)
include(ExternalProject)

INCLUDE_DIRECTORIES("include")

set(SPDLOG_INSTALL_LOCATION ${CMAKE_BINARY_DIR}/spdlog)
set(ERROR_FLAGS "-Wall -Werror -Wextra -Wfatal-errors -pedantic-errors")

ExternalProject_Add(SPDLOG
        GIT_REPOSITORY https://github.com/gabime/spdlog
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${SPDLOG_INSTALL_LOCATION}
        )


include_directories(src/places/include)
include_directories(src/threads/include)
include_directories(src/controllers/include)

ADD_EXECUTABLE(LifeSimulation
        src/main.cpp
        src/controllers/include/MainController.hpp
        src/controllers/MainController.cpp
        src/threads/Human.cpp
        src/threads/include/Human.hpp
        src/places/Place.cpp
        src/places/include/Place.hpp
        src/places/Restaurant.cpp src/places/include/Restaurant.h src/threads/IHuman.h src/console/Console.cpp src/console/include/Console.hpp src/places/Basketball.cpp src/places/include/Basketball.hpp src/places/Hotel.cpp src/places/include/Hotel.h src/places/Barber.cpp src/places/include/Barber.h src/places/ChessClub.cpp src/places/include/ChessClub.h)

FIND_PACKAGE(Curses REQUIRED)
FIND_PACKAGE(Threads REQUIRED)

target_link_libraries(LifeSimulation ${CURSES_LIBRARIES})
target_link_libraries(LifeSimulation ${CMAKE_THREAD_LIBS_INIT})

include_directories(${SPDLOG_INSTALL_LOCATION}/include)
link_directories(${SPDLOG_INSTALL_LOCATION}/lib)

add_dependencies(LifeSimulation SPDLOG)
