cmake_minimum_required(VERSION 3.15)
project(The_Hairdressers)

set(CMAKE_CXX_STANDARD 17)

find_package(Threads REQUIRED )
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(The_Hairdressers Source/main.cpp Source/Hairdresser.cpp Headers/Hairdresser.h Headers/Parameters.h Source/Customer.cpp Headers/Customer.h Source/Scissors.cpp Headers/Scissors.h Source/Salon.cpp Headers/Salon.h Source/Visualizer.cpp Headers/Visualizer.h Source/City.cpp Headers/City.h Source/Supplies.cpp Headers/Supplies.h Source/Common.cpp Headers/Common.h)

target_link_libraries(The_Hairdressers pthread ${CURSES_LIBRARIES})