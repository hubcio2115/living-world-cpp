cmake_minimum_required(VERSION 3.25)
project(01_living_world_hubcio2115)

set(CMAKE_CXX_STANDARD 23)
add_executable(01_living_world_hubcio2115 main.cpp)

add_subdirectory(src)
add_subdirectory(src/animals)
add_subdirectory(src/plants)
add_subdirectory(src/utils)


include(FetchContent)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

target_link_libraries(01_living_world_hubcio2115 PRIVATE nlohmann_json::nlohmann_json)
