cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(task_tracker VERSION 1.0 LANGUAGES CXX)

# libraries
set(JSON_Install OFF CACHE INTERNAL "")
add_subdirectory(include/nlohmann_json)


add_executable(task_tracker main.cpp)
target_link_libraries(task_tracker PRIVATE nlohmann_json::nlohmann_json)
set_property(TARGET task_tracker PROPERTY CXX_STANDARD 17)