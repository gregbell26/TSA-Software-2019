cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 17)

project(ArcylicBackend)

set(ABSTRATION_LAYER_SRC AbstractionLayer/acrylic_GFX.cpp AbstractionLayer/acrylic_saveEngine.cpp AbstractionLayer/TaskScheduler.cpp)

set(BACKEND_SRC BackendAPI/CPU/acrylic_CPUMan.cpp BackendAPI/FileSystem/acrylic_fileSystem.cpp BackendAPI/Graphics/GraphicsBackend/vulkan.cpp BackendAPI/Graphics/acrylic_graphicsBackend.cpp)

set(ACRLYIC_BACKEND_SRC acrylic_engine.cpp acrylic_interactionEngine.cpp acrylic_physicsEngine.cpp acrylic_renderEngine.cpp)

set(ABSTRATION_LAYER_HEADER AbstractionLayer/acrylic_GFX.hpp AbstractionLayer/acrylic_saveEngine.hpp AbstractionLayer/TaskScheduler.hpp)

set(BACKEND_HEADER BackendAPI/CPU/acrylic_CPUMan.hpp BackendAPI/FileSystem/acrylic_fileSystem.hpp BackendAPI/Graphics/GraphicsBackend/vulkan.hpp BackendAPI/Graphics/acrylic_graphicsBackend.hpp BackendAPI/Graphics/GraphicsBackend/glfw.hpp)

set(ACRLYIC_BACKEND_HEADER acrylic_engine.hpp acrylic_interactionEngine.hpp acrylic_physicsEngine.hpp acrylic_renderEngine.hpp)

set(ACRYLIC_BACKEND ${ABSTRATION_LAYER_SRC} ${BACKEND_SRC} ${ACRLYIC_BACKEND_SRC} ${ABSTRATION_LAYER_HEADER} ${BACKEND_HEADER} ${ACRLYIC_BACKEND_HEADER})

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    include_directories(/usr/local/include)

    add_compile_definitions(MACOS)

elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    #We have to do this because windows doesn't havea central include directory
    #Vulkan
    include_directories(C:/SDKS/VulkanSDK/1.1.114.0/Include)
    #GLM
    include_directories(C:/SDKS/GLM0.9)
    #GLFW
    include_directories(C:/SDKS/GLFW3.3/glfw-3.3.bin.WIN64/include)
    #Load Modules
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

    #Disable MSVC Bullshit
    SET( CMAKE_SHARED_LINKER_FLAGS ${CMAKE_SHARED_LINKER_FLAGS} "/NODEFAULTLIBS:MSVCRT" )

    add_compile_definitions(WINDOWS)

elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    message(AUTHOR_WARNING "Building on Linux has not been tested. Please use macOS or Windows to build")
    include_directories(/usr/local/include)

    add_compile_definitions(LINUX)

else()
    message(FATAL_ERROR "Unable to detect operating system. Build halted")
endif()

#Lib Includes
find_package(vulkan REQUIRED)
find_package(glfw3 3.3 REQUIRED)

add_library(ArcylicBackend SHARED ${ACRYLIC_BACKEND})

target_link_libraries(ArcylicBackend Vulkan::Vulkan)


if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    target_link_libraries(ArcylicBackend ${GLFW3_LIBRARY})#For somereason this only works on AMD64 for windows. Not AMD64 for mac
else()
    target_link_libraries(ArcylicBackend glfw)
endif()
