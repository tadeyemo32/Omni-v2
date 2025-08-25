cmake_minimum_required(VERSION 3.15)
project(Omni VERSION 2.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add src directory to include path
include_directories(
    ${CMAKE_SOURCE_DIR}/deps
    ${CMAKE_SOURCE_DIR}/src
)

# Server executable
add_executable(omni_server src/server/src/main.cpp)

# Client executable  
add_executable(omni_client src/client/src/main.cpp)