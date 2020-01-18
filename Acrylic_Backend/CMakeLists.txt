#AcrylicEngine
cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 17)

project(AcrylicEngine)

#include TriHard Studios Helper Libs
include_directories(./BackendAPIs/BackendAPIs/required/trihardstudios/include)

#Include OpenGL
include_directories(./BackendAPIs/Plexi2DRenderer/GraphicsAPIs/required/glad/include)

#Include GLM
include_directories(./BackendAPIs/Plexi2DRenderer/GraphicsAPIs/required/glm/include)

#Include GLFW3
include_directories(./BackendAPIs/BackendAPIs/required/GLFW3/include)

#Inlcude FreeType for font loading and rastiation
include_directories(./../BackendAPIs/required/FreeType/include)

#include Nlohmann JSON
include_directories(./BackendAPIs/BackendAPIs/required/nlohmannJSON/include)



#Load cmake modules for GLFW and Shaderc_Combined
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

add_subdirectory(./BackendAPIs/AcrylicSaveEngine)
add_subdirectory(./BackendAPIs/Plexi2DRenderer)

set(CPU_SOURCE BackendAPIs/CPU/TaskScheduler.cpp)
set(CPU_HEADER BackendAPIs/CPU/TaskScheduler.hpp)

set(USER_INPUT_HEADER UserInput/Input.hpp UserInput/KeyInput.hpp UserInput/MouseInput.hpp)
set(USER_INPUT_SOURCE UserInput/Input.cpp UserInput/Inputs.cpp UserInput/KeyInput.cpp UserInput/MouseInput.cpp)

set(USER_INPUT_HEADER )
set(USER_INPUT_SOURCE )

set(SOURCE_FILES ${CPU_SOURCE} ${USER_INPUT_SOURCE} acrylic_engine.cpp acrylic_interactionEngine.cpp acrylic_physicsEngine.cpp Random.cpp)
set(HEADER_FILES ${CPU_HEADER} ${USER_INPUT_HEADER} acrylic_engine.hpp acrylic_interactionEngine.hpp acrylic_physicsEngine.hpp Random.h)

set(TEST_CODE main.nfp.cpp)

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    add_compile_definitions(MACOS)

elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    #Disable MSVC Bullshit
    SET( CMAKE_SHARED_LINKER_FLAGS ${CMAKE_SHARED_LINKER_FLAGS} "/NODEFAULTLIBS:LIBCMT" )
    SET( CMAKE_SHARED_LINKER_FLAGS ${CMAKE_SHARED_LINKER_FLAGS} "/NODEFAULTLIBS:MSVCRT" )
    SET( CMAKE_SHARED_LINKER_FLAGS ${CMAKE_SHARED_LINKER_FLAGS} "/NODEFAULTLIBS:MSVCPRTD" )

    add_compile_definitions(WINDOWS)

elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    message(AUTHOR_WARNING "Building on Linux has not been tested. Please use macOS or Windows to build")

    add_compile_definitions(LINUX)

else()
    message(FATAL_ERROR "Unable to detect operating system. Build halted")
endif()

#Disable GLFW includes
add_compile_definitions(GLFW_INCLUDE_NONE)

#add_library(AcrylicEngine SHARED ${SOURCE_FILES} ${HEADER_FILES}) #We are going to staticly link til we have exports
add_library(AcrylicEngine STATIC ${SOURCE_FILES} ${HEADER_FILES})
add_executable(AcrylicTestinator1000 ${TEST_CODE})

target_link_libraries(AcrylicEngine AcrylicSaveEngine)
target_link_libraries(AcrylicEngine Plexi2DRenderer)
#target_link_libraries(AcrylicEngine A2D_log)

target_link_libraries(AcrylicTestinator1000 AcrylicEngine)


#Copy all assets - Note these are for debugging

#Shaders
add_custom_command(
        TARGET AcrylicTestinator1000 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_SOURCE_DIR}/Acrylic_Backend/BackendAPIs/Plexi2DRenderer/plexi_shaders
                ${CMAKE_CURRENT_BINARY_DIR}/plexi_shaders
)

#Textures
add_custom_command(
        TARGET AcrylicTestinator1000 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Acrylic_Backend/TestData/textures
        ${CMAKE_CURRENT_BINARY_DIR}/textures
)

#Fonts
add_custom_command(
        TARGET AcrylicTestinator1000 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Acrylic_Backend/TestData/fonts
        ${CMAKE_CURRENT_BINARY_DIR}/fonts
)



