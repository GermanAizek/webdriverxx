cmake_minimum_required(VERSION 3.5)
project(webdriverxx)

if(NOT MSVC OR NOT MSYS OR NOT MINGW)
	include(CheckCXXCompilerFlag)
	CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
	CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)

    if(COMPILER_SUPPORTS_CXX11)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    elseif(COMPILER_SUPPORTS_CXX0X)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
    endif()
endif()

enable_testing()

include_directories(${CMAKE_SOURCE_DIR}/include)

if(WIN32)
	# curl
	#add_subdirectory(${CMAKE_SOURCE_DIR}/thirdparty/curl)
	include_directories(${CMAKE_SOURCE_DIR}/thirdparty/curl/include)
	link_directories(${CMAKE_SOURCE_DIR}/thirdparty/curl/lib)
	add_subdirectory(${CMAKE_SOURCE_DIR}/test)
elseif(UNIX AND NOT APPLE)
	find_package(CURL REQUIRED)
	include_directories(${CURL_INCLUDE_DIR})
	
	install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/
                  DESTINATION include/${PROJECT_NAME}
                  FILES_MATCHING PATTERN "*")
endif()