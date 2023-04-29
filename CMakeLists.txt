cmake_minimum_required(VERSION 3.25)
project(01_living_world_hubcio2115)

set(CMAKE_CXX_STANDARD 23)

add_executable(01_living_world_hubcio2115
        main.cpp
        src/World.cpp
        src/Position.cpp
        src/Organism.cpp
        src/plants/Plant.cpp
        src/animals/Animal.cpp
        )
