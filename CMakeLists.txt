
cmake_minimum_required(VERSION 3.15)
project(Omni VERSION 2.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_definitions(CPPHTTPLIB_OPENSSL_SUPPORT)

# Export compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find OpenSSL
find_package(OpenSSL REQUIRED)

# ---- Dependencies ----
include_directories(${CMAKE_SOURCE_DIR}/deps)

# Find GLFW (installed via package manager, e.g. brew/apt/vcpkg)
find_package(glfw3 3.3 REQUIRED)

# ---- ImGui ----
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/deps/imgui)
add_library(imgui
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)
target_include_directories(imgui PUBLIC
    ${IMGUI_DIR}
    ${IMGUI_DIR}/backends
)

# ---- Optional: ImPlot ----
set(IMPLOT_DIR ${CMAKE_SOURCE_DIR}/deps/implot)
add_library(implot
    ${IMPLOT_DIR}/implot.cpp
    ${IMPLOT_DIR}/implot_items.cpp
)
target_include_directories(implot PUBLIC ${IMPLOT_DIR})
target_link_libraries(implot PUBLIC imgui)

# ---- Collect server sources ----
set(SERVER_SOURCES
    ${CMAKE_SOURCE_DIR}/server/src/main.cpp
    ${CMAKE_SOURCE_DIR}/server/src/server.cpp
    ${CMAKE_SOURCE_DIR}/server/src/server_auth.cpp
    ${CMAKE_SOURCE_DIR}/server/src/server_request_hadler.cpp
)

# ---- Collect client sources ----
file(GLOB_RECURSE CLIENT_SOURCES
    ${CMAKE_SOURCE_DIR}/client/src/*.cpp
)

# ---- Executables ----
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
target_link_libraries(omni_client PRIVATE
    OpenSSL::SSL OpenSSL::Crypto
    imgui glfw
    implot             # optional if you want charts
)
