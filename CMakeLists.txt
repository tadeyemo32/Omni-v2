cmake_minimum_required(VERSION 3.15)
project(Omni VERSION 2.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

include_directories(${CMAKE_SOURCE_DIR}/deps)

file(GLOB SERVER_SRC
    "${CMAKE_SOURCE_DIR}/src/server/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/server/*.hpp"
)
add_executable(omni_server ${SERVER_SRC})

file(GLOB CLIENT_SRC
    "${CMAKE_SOURCE_DIR}/src/client/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/client/*.hpp"
)
add_executable(omni_client ${CLIENT_SRC})

