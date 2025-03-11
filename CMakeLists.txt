cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(task_tracker VERSION 1.0 LANGUAGES CXX)

# libraries
set(JSON_Install OFF CACHE INTERNAL "")
add_subdirectory(include/nlohmann_json)

# headers
add_library(helper    STATIC helper.hpp)
add_library(task      STATIC task.hpp)
add_library(save_load STATIC save_load.hpp)
set_property(TARGET helper task save_load PROPERTY LINKER_LANGUAGE CXX)


add_executable(task_tracker main.cpp)
target_link_libraries(task_tracker PRIVATE nlohmann_json::nlohmann_json helper task save_load)
set_property(TARGET task_tracker PROPERTY CXX_STANDARD 17)