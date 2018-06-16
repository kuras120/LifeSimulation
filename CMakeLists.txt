CMAKE_MINIMUM_REQUIRED(VERSION 3.9)
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

ADD_EXECUTABLE(LifeSimulation
        src/main.cpp 
        src/threads/Human.cpp 
        src/threads/include/Human.hpp
        src/places/Place.cpp 
        src/places/include/Place.hpp
        )

FIND_PACKAGE(Curses REQUIRED)
FIND_PACKAGE(Threads REQUIRED)

target_link_libraries(LifeSimulation ${CURSES_LIBRARIES})
target_link_libraries(LifeSimulation ${CMAKE_THREAD_LIBS_INIT})

include_directories(${SPDLOG_INSTALL_LOCATION}/include)
link_directories(${SPDLOG_INSTALL_LOCATION}/lib)

add_dependencies(LifeSimulation SPDLOG)
