cmake_minimum_required(VERSION 3.15)
project(Omni VERSION 2.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output binaries into bin/
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Export compile_commands.json (useful for clangd, etc.)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find OpenSSL
find_package(OpenSSL REQUIRED)

# ---- Dependencies (header-only) ----
include_directories(${CMAKE_SOURCE_DIR}/deps)

# ---- Collect sources ----
file(GLOB_RECURSE SERVER_SOURCES
    ${CMAKE_SOURCE_DIR}/server/src/*.cpp
)

file(GLOB_RECURSE CLIENT_SOURCES
    ${CMAKE_SOURCE_DIR}/client/src/*.cpp
)

# Collect test sources
file(GLOB_RECURSE SERVER_TEST_SOURCES
    ${CMAKE_SOURCE_DIR}/server/tests/*.cpp
)

file(GLOB_RECURSE CLIENT_TEST_SOURCES
    ${CMAKE_SOURCE_DIR}/client/tests/*.cpp
)

# Add compiler definitions for SSL support
add_compile_definitions(CPPHTTPLIB_OPENSSL_SUPPORT)

# ---- Main Server ----
add_executable(omni_server ${SERVER_SOURCES})

target_include_directories(omni_server PRIVATE
    ${CMAKE_SOURCE_DIR}/server/include
    ${CMAKE_SOURCE_DIR}/deps
)

target_link_libraries(omni_server PRIVATE OpenSSL::SSL OpenSSL::Crypto)

# ---- Main Client ----
add_executable(omni_client ${CLIENT_SOURCES})

target_include_directories(omni_client PRIVATE
    ${CMAKE_SOURCE_DIR}/client/include
    ${CMAKE_SOURCE_DIR}/deps
)

target_link_libraries(omni_client PRIVATE OpenSSL::SSL OpenSSL::Crypto)

# ---- Test Binaries ----
# Server Test
add_executable(server_test ${SERVER_TEST_SOURCES})

target_include_directories(server_test PRIVATE
    ${CMAKE_SOURCE_DIR}/server/include
    ${CMAKE_SOURCE_DIR}/deps
)

target_link_libraries(server_test PRIVATE OpenSSL::SSL OpenSSL::Crypto)

# Client Test
add_executable(client_test ${CLIENT_TEST_SOURCES})

target_include_directories(client_test PRIVATE
    ${CMAKE_SOURCE_DIR}/client/include
    ${CMAKE_SOURCE_DIR}/deps
)

target_link_libraries(client_test PRIVATE OpenSSL::SSL OpenSSL::Crypto)

# Create a test directory in bin
add_custom_command(TARGET server_test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/bin/tests
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:server_test> ${CMAKE_SOURCE_DIR}/bin/tests/
)

add_custom_command(TARGET client_test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/bin/tests
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:client_test> ${CMAKE_SOURCE_DIR}/bin/tests/
)