cmake_minimum_required(VERSION 3.15)
project(Omni VERSION 2.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output binaries into bin/
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Export compile_commands.json (useful for clangd, etc.)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ---- Dependencies (header-only) ----
include_directories(${CMAKE_SOURCE_DIR}/deps)

# ---- Collect sources ----
file(GLOB_RECURSE SERVER_SOURCES
    ${CMAKE_SOURCE_DIR}/server/src/*.c
    ${CMAKE_SOURCE_DIR}/server/src/*.cpp
)

file(GLOB_RECURSE CLIENT_SOURCES
    ${CMAKE_SOURCE_DIR}/client/src/*.c
    ${CMAKE_SOURCE_DIR}/client/src/*.cpp
)

# ---- Server ----
add_executable(omni_server ${SERVER_SOURCES})

target_include_directories(omni_server PRIVATE
    ${CMAKE_SOURCE_DIR}/server/include
    ${CMAKE_SOURCE_DIR}/deps
    /opt/homebrew/opt/openssl/include
)

target_link_directories(omni_server PRIVATE /opt/homebrew/opt/openssl/lib)
target_link_libraries(omni_server PRIVATE ssl crypto)

# ---- Client ----
add_executable(omni_client ${CLIENT_SOURCES})

target_include_directories(omni_client PRIVATE
    ${CMAKE_SOURCE_DIR}/client/include
    ${CMAKE_SOURCE_DIR}/deps
    /opt/homebrew/opt/openssl/include
)

target_link_directories(omni_client PRIVATE /opt/homebrew/opt/openssl/lib)
target_link_libraries(omni_client PRIVATE ssl crypto)
