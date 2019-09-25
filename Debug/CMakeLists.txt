cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 17)

set(DEBUG_SRC log.cpp)
set(DEBUG_HEADER log.h)

set(DEBUG ${DEBUG_SRC} ${DEBUG_HEADER})

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    add_compile_definitions(MACOS)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    add_compile_definitions(WINDOWS)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    add_compile_definitions(LINUX)
endif()


add_executable(Arcylic2D_Debug ${DEBUG})
#add_library(Acrylic2D_Debug STATIC ${DEBUG})