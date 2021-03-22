cmake_minimum_required(VERSION 3.5)

project(example_start_browsers LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(CURL_STATICLIB "Set to ON to build libcurl with static linking." ON)

if(WIN32)
    add_definitions("-DCURL_STATICLIB")
    set(CURL_LIBRARY "libcurl.lib")
else()
    set(CURL_LIBRARY "-lcurl")
endif()

find_package(CURL REQUIRED)
target_link_libraries(example_start_browsers CURL::libcurl)
include_directories(${CURL_INCLUDE_DIR})
link_libraries(${CURL_LIBRARIES})

add_executable(example_start_browsers main.cpp)
include_directories(../../src/include)
