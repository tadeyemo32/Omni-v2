cmake_minimum_required(VERSION 3.15)
project(Omni VERSION 2.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_definitions(CPPHTTPLIB_OPENSSL_SUPPORT)

# Export compile_commands.json (useful for clangd, etc.)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find OpenSSL
find_package(OpenSSL REQUIRED)

# ---- Dependencies (header-only) ----
include_directories(${CMAKE_SOURCE_DIR}/deps)

# ---- Collect server sources ----
set(SERVER_SOURCES
    ${CMAKE_SOURCE_DIR}/server/src/main.cpp
    ${CMAKE_SOURCE_DIR}/server/src/server.cpp
    ${CMAKE_SOURCE_DIR}/server/src/server_auth.cpp
    ${CMAKE_SOURCE_DIR}/server/src/server_request_hadler.cpp  # include request handler
)

# ---- Collect client sources ----
file(GLOB_RECURSE CLIENT_SOURCES
    ${CMAKE_SOURCE_DIR}/client/src/*.cpp
)

# ---- Main Executables (output to bin/) ----
# Server
add_executable(omni_server ${SERVER_SOURCES})
set_target_properties(omni_server PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)
target_include_directories(omni_server PRIVATE
    ${CMAKE_SOURCE_DIR}/server/include
    ${CMAKE_SOURCE_DIR}/deps
)
target_link_libraries(omni_server PRIVATE OpenSSL::SSL OpenSSL::Crypto)

# Client
add_executable(omni_client ${CLIENT_SOURCES})
set_target_properties(omni_client PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)
target_include_directories(omni_client PRIVATE
    ${CMAKE_SOURCE_DIR}/client/include
    ${CMAKE_SOURCE_DIR}/deps
)
target_link_libraries(omni_client PRIVATE OpenSSL::SSL OpenSSL::Crypto)
