cmake_minimum_required(VERSION 3.5)

project(example_find_send LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(CURL_STATICLIB "Set to ON to build libcurl with static linking." ON)

if(WIN32)
    add_definitions("-DCURL_STATICLIB")
endif()

set(CURL_LIBRARY "-lcurl")
find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})
link_libraries(${CURL_LIBRARIES})

add_executable(example_find_send main.cpp)
include_directories(../../src/include)
