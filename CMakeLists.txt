cmake_minimum_required(VERSION 3.10)
project(GitHubStats)

set(CMAKE_CXX_STANDARD 17)

find_package(CURL REQUIRED)

add_executable(gstat main.cpp)

target_link_libraries(gstat PRIVATE CURL::libcurl)

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz)
FetchContent_MakeAvailable(json)

target_link_libraries(gstat PRIVATE nlohmann_json::nlohmann_json)
