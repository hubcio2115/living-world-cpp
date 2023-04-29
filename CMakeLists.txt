cmake_minimum_required(VERSION 3.25)
project(01_living_world_hubcio2115)

set(CMAKE_CXX_STANDARD 23)

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

add_executable(01_living_world_hubcio2115
        main.cpp
        src/World.cpp
        src/Position.cpp
        src/Organism.cpp
        src/plants/Plant.cpp
        src/animals/Animal.cpp
        src/plants/Dandelion.h
        src/plants/Grass.h
        src/animals/Sheep.h
        src/animals/Wolf.h
        src/animals/Wolf.cpp
        src/animals/Sheep.cpp
        src/plants/Dandelion.cpp
        src/plants/Grass.cpp
        src/plants/Toadstool.cpp
        )

target_link_libraries(01_living_world_hubcio2115 PRIVATE nlohmann_json::nlohmann_json)
