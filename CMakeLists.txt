cmake_minimum_required(VERSION 3.20) # Using a newer version for better cross-platform support
cmake_policy(SET CMP0115 NEW)
cmake_policy(SET CMP0069 NEW)

# Project settings
project(Automaton)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE) # Link-time optimization

# Enable SIMD optimizations for MSVC
if(MSVC)
    add_compile_options(/arch:AVX2)
endif()

# Production build flag
option(PRODUCTION_BUILD "Enable production build settings" OFF)

# MSVC runtime library settings
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

# Add third-party libraries
#add_subdirectory(thirdparty/glm)


# Include source files
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# Main executable
add_executable("${CMAKE_PROJECT_NAME}" src/main.cpp)
target_sources("${CMAKE_PROJECT_NAME}" PRIVATE ${MY_SOURCES})

# Include directories
target_include_directories("${CMAKE_PROJECT_NAME}" PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")

if(PRODUCTION_BUILD)
    target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="./resources/")
    target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC PRODUCTION_BUILD=1)
else()
    target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/")
    target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC PRODUCTION_BUILD=0)
endif()

# Platform-specific configurations
if(MSVC)
    target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC _CRT_SECURE_NO_WARNINGS)
    set_target_properties("${CMAKE_PROJECT_NAME}" PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
endif()

if(LINUX OR APPLE)
    find_package(CURL REQUIRED)
    target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE CURL::libcurl)
else()
endif()

# Link libraries
#target_link_libraries("${CMAKE_PROJECT_NAME}" PRIVATE glm )
