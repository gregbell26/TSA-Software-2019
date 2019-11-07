#AcrylicEngine
cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 17)

project(AcrylicEngine)

add_subdirectory(./BackendAPIs/AcrylicSaveEngine)
add_subdirectory(./BackendAPIs/Plexi2DRenderer)

set(CPU_SOURCE BackendAPIs/CPU/TaskScheduler.cpp)
set(CPU_HEADER BackendAPIs/CPU/TaskScheduler.hpp)
set(SOURCE_FILES ${CPU_SOURCE} acrylic_engine.cpp acrylic_interactionEngine.cpp acrylic_physicsEngine.cpp)
set(HEADER_FILES ${CPU_HEADER} acrylic_engine.hpp acrylic_interactionEngine.hpp acrylic_physicsEngine.hpp)

#add_library(AcrylicEngine SHARED ${SOURCE_FILES} ${HEADER_FILES}) #We are going to staticly link til we have exports
add_library(AcrylicEngine STATIC ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries(AcrylicEngine AcrylicSaveEngine)
#target_link_libraries(AcrylicEngine Plexi2DRenderer)


