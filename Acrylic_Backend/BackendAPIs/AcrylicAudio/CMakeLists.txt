cmake_minimum_required(VERSION 3.13)

project(AcrylicAudio)

set(CMAKE_CXX_STANDARD 17)


#include OpenAL - The audio lib we are using
add_subdirectory(AudioAPIs/OpenAL)
include_directories(AudioAPIs/OpenAL/include)

set(SOURCE_FILES audio.cpp)
set(HEADER_FILES audio.hpp)

set(TEST_SOURCE main.nfp.cpp)

add_library(AcrylicAudio STATIC ${SOURCE_FILES} ${HEADER_FILES} )
target_link_libraries(AcrylicAudio OpenAL)

add_executable(AudioTestinator1000 ${TEST_SOURCE})
target_link_libraries(AudioTestinator1000 AcrylicAudio)

