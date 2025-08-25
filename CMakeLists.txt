cmake_minimum_required(VERSION 3.15)

project(Omni VERSION 2.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

include_directories(${CMAKE_SOURCE_DIR}/deps)

file(GLOB_RECURSE SERVER_SRC
    "${CMAKE_SOURCE_DIR}/src/server/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/server/include/*.hpp"
    "${CMAKE_SOURCE_DIR}/src/server/include/*.h"
)

add_executable(omni_server ${SERVER_SRC})
target_include_directories(omni_server PRIVATE
    ${CMAKE_SOURCE_DIR}/src/server/include
)

file(GLOB_RECURSE CLIENT_SRC
    "${CMAKE_SOURCE_DIR}/src/client/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/src/client/include/*.hpp"
    "${CMAKE_SOURCE_DIR}/src/client/include/*.h"
)

add_executable(omni_client ${CLIENT_SRC})
target_include_directories(omni_client PRIVATE
    ${CMAKE_SOURCE_DIR}/src/client/include
)

source_group(TREE ${CMAKE_SOURCE_DIR}/src PREFIX "Source" FILES ${SERVER_SRC} ${CLIENT_SRC})

