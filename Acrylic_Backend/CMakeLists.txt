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

#Load cmake modules for GLFW and Shaderc_Combined
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    include_directories(/usr/local/include)

    add_compile_definitions(MACOS)

elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    #We have to do this because windows doesn't havea central include directory
    #PlexiBackend_Vulkan
    include_directories(C:/SDKS/VulkanSDK/1.1.114.0/Include)
    #GLM
    include_directories(C:/SDKS/GLM0.9)
    #GLFW
    include_directories(C:/SDKS/GLFW3.3/glfw-3.3.bin.WIN64/include)

    #Disable MSVC Bullshit
    SET( CMAKE_SHARED_LINKER_FLAGS ${CMAKE_SHARED_LINKER_FLAGS} "/NODEFAULTLIBS:LIBCMT" )
    SET( CMAKE_SHARED_LINKER_FLAGS ${CMAKE_SHARED_LINKER_FLAGS} "/NODEFAULTLIBS:MSVCRT" )
    SET( CMAKE_SHARED_LINKER_FLAGS ${CMAKE_SHARED_LINKER_FLAGS} "/NODEFAULTLIBS:MSVCPRTD" )

    add_compile_definitions(WINDOWS)

elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    message(AUTHOR_WARNING "Building on Linux has not been tested. Please use macOS or Windows to build")
    include_directories(/usr/local/include)

    add_compile_definitions(LINUX)

else()
    message(FATAL_ERROR "Unable to detect operating system. Build halted")
endif()


#add_library(AcrylicEngine SHARED ${SOURCE_FILES} ${HEADER_FILES}) #We are going to staticly link til we have exports
add_library(AcrylicEngine STATIC ${SOURCE_FILES} ${HEADER_FILES})

#target_link_libraries(AcrylicEngine AcrylicSaveEngine)
#target_link_libraries(AcrylicEngine Plexi2DRenderer)


