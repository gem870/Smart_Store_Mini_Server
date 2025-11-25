cmake_minimum_required(VERSION 3.16)
project(SmartStoreServer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ServerApp server.cpp)

target_include_directories(ServerApp
    PRIVATE ${CMAKE_SOURCE_DIR}/asio/include
)

target_link_libraries(ServerApp PRIVATE ws2_32)

# ✅ Define Windows version (0x0A00 = Windows 10)
target_compile_definitions(ServerApp PRIVATE _WIN32_WINNT=0x0A00)