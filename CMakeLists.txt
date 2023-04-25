cmake_minimum_required(VERSION 3.25)
project(01_living_world_hubcio2115)

set(CMAKE_CXX_STANDARD 23)

add_executable(01_living_world_hubcio2115 src/Animal.cpp main.cpp src/Organism.cpp src/Plant.cpp src/Position.cpp src/World.cpp)
