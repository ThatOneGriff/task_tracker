cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(task_tracker VERSION 1.0 LANGUAGES CXX)

# headers
add_library(datetime    STATIC datetime.hpp)
add_library(strings     STATIC strings.hpp)
add_library(ui          STATIC ui.hpp)
set_property(TARGET datetime strings ui PROPERTY LINKER_LANGUAGE CXX)