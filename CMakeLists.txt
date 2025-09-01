cmake_minimum_required(VERSION 3.10)
project(GitHubStats)

set(CMAKE_CXX_STANDARD 17)

find_package(CURL REQUIRED)

add_executable(gstat main.cpp)

target_link_libraries(gstat PRIVATE CURL::libcurl)
