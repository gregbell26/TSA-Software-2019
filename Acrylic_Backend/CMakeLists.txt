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
set(DYNAMIC_MEMORY BackendAPIs/Dynamic memory/Hash_Table.cpp)
set(DYNAMIC_MEMORY BackendAPIs/Dynamic memory/Hash_Table.h)
set(SOURCE_FILES ${CPU_SOURCE} acrylic_engine.cpp acrylic_interactionEngine.cpp acrylic_physicsEngine.cpp)
set(HEADER_FILES ${CPU_HEADER} acrylic_engine.hpp acrylic_interactionEngine.hpp acrylic_physicsEngine.hpp UserInput.hpp UserInputMap.cpp UserInputMap.hpp Random.cpp Random.h)

set(TEST_CODE main.nfp.cpp)

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
#    include_directories(/usr/local/include)

    add_compile_definitions(MACOS)

elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    #We have to do this because windows doesn't havea central include directory
    #PlexiBackend_Vulkan
#    include_directories(C:/SDKS/VulkanSDK/1.1.114.0/Include)
    #GLM
#    include_directories(C:/SDKS/GLM0.9)
    #JOSN BOI
#    include_directories(C:/SDKS/NlohmannJSON/include)
    #GLFW
#    include_directories(C:/SDKS/GLFW3.3/glfw-3.3.bin.WIN64/include)

    #Disable MSVC Bullshit
    SET( CMAKE_SHARED_LINKER_FLAGS ${CMAKE_SHARED_LINKER_FLAGS} "/NODEFAULTLIBS:LIBCMT" )
    SET( CMAKE_SHARED_LINKER_FLAGS ${CMAKE_SHARED_LINKER_FLAGS} "/NODEFAULTLIBS:MSVCRT" )
    SET( CMAKE_SHARED_LINKER_FLAGS ${CMAKE_SHARED_LINKER_FLAGS} "/NODEFAULTLIBS:MSVCPRTD" )

    add_compile_definitions(WINDOWS)

elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    message(AUTHOR_WARNING "Building on Linux has not been tested. Please use macOS or Windows to build")
#    include_directories(/usr/local/include)

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
