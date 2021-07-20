cmake_minimum_required(VERSION 3.5)

project(example_start_browsers LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(CURL_STATICLIB "Set to ON to build libcurl with static linking." ON)

if(CURL_STATICLIB)
    add_definitions("-DCURL_STATICLIB")
endif()

set(CURL_LIBRARY "-lcurl")

if(WIN32)
    set(CURL_INCLUDE_DIR "${CMAKE_SOURCE_DIR}\\..\\..\\src\\thirdparty\\curl\\include")
    set(CURL_LIBRARIES "${CMAKE_SOURCE_DIR}\\..\\..\\src\\thirdparty\\curl\\lib")
#else()
#    find_package(CURL REQUIRED)
endif()

find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})
link_directories(${CURL_LIBRARIES})

add_executable(example_start_browsers main.cpp)
include_directories("${CMAKE_SOURCE_DIR}/../../src/include")
target_link_libraries(example_start_browsers curl wldap32 ws2_32 Crypt32.lib Wldap32 Normaliz)
