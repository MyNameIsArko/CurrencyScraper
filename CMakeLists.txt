cmake_minimum_required(VERSION 3.22)
project(CurrencyScraper)

set(CMAKE_CXX_STANDARD 11)

add_executable(CurrencyScraper main.cpp)

include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
        GIT_TAG db351ffbbadc6c4e9239daaa26e9aefa9f0ec82d) # The commit hash for 1.8.1. Replace with the latest from: https://github.com/libcpr/cpr/releases
FetchContent_MakeAvailable(cpr)

target_link_libraries(CurrencyScraper PRIVATE cpr::cpr)