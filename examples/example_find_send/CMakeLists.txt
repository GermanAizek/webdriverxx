cmake_minimum_required(VERSION 3.5)

project(example_find_send LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(CURL_STATICLIB "Set to ON to build libcurl with static linking." ON)

if(CURL_STATICLIB)
    add_definitions("-DCURL_STATICLIB")
endif()

if(WIN32)
    set(CURL_LIBRARY "libcurl.lib")
    set(CURL_INCLUDE_DIR "../webdriverxx/src/thirdparty/curl/include")
    set(CURL_LIBRARIES "../webdriverxx/src/thirdparty/curl/lib")
else()
    set(CURL_LIBRARY "-lcurl")
    find_package(CURL REQUIRED)
endif()

include_directories(${CURL_INCLUDE_DIR})
link_libraries(${CURL_LIBRARIES})

add_executable(example_find_send main.cpp)
include_directories("../../src/include")
