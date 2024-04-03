cmake_minimum_required(VERSION 3.12)
project(leaf)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
#set(CMAKE_VERBOSE_MAKEFILE ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -fno-strict-aliasing -fno-omit-frame-pointer -g -O0 -ggdb")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fno-strict-aliasing -fno-omit-frame-pointer -g -O0 -ggdb")

# pthread
set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)
set(LINK_LIBS Threads::Threads) #

set(SPDLOG_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/spdlog/include)

MESSAGE(STATUS "SDPLOG INCLUDE DIRS ${SPDLOG_INCLUDE_DIRS}")

set(RAPIDJSON_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/rapidjson/include)

MESSAGE(STATUS "RAPIDJSON INCLUDE DIRS ${RAPIDJSON_INCLUDE_DIR}")

add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME} PRIVATE 
    log.cpp
    timestamp.cpp
    )

target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${SPDLOG_INCLUDE_DIRS} ${RAPIDJSON_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} PRIVATE ${LINK_LIBS})
