cmake_minimum_required(VERSION 3.12)

project(Acrylic2D_Helper_Lib)
set(CMAKE_CXX_STANDARD 17)

add_compile_definitions(${CMAKE_SYSTEM_NAME})

message("TriHard Studios Acrylic2D Helper Libarary")
message("Contains: Logger, Profiler ")


set(LOG_SOURCE ./log/log.cpp)

set(LOG_INCLUDE ./include/ths/log.hpp)

set(PROFILE_SOURCE ./profile/profile.cpp )

set(PROFILE_INCLUDE ./include/ths/profile.hpp)

#set(TEST_SOURCE ./UnitTests.nfp/main.nfp.cpp)



add_library(A2D_log STATIC ${LOG_SOURCE} ${LOG_INCLUDE})
add_library(A2D_profile STATIC ${PROFILE_SOURCE} ${PROFILE_INCLUDE})

#add_executable(A2D_LibTestinator1000 ${TEST_SOURCE})
#target_link_libraries(A2D_LibTestinator1000 A2D_log)
#target_link_libraries(A2D_LibTestinator1000 A2D_profile)