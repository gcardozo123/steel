cmake_minimum_required(VERSION 3.1)

if(${CMAKE_VERSION} VERSION_LESS 3.15)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
    cmake_policy(VERSION 3.15)
endif()

# issue [https://gitlab.kitware.com/cmake/cmake/issues/19409] does not allow to do this:
#set(CMAKE_GENERATOR_PLATFORM "Visual Studio 16 2019")
# it's necessary to run with: cmake -G "Visual Studio 16 2019"
project(steel 
	DESCRIPTION "one day this will be a 2D game framework"
	VERSION 0.0.1
	LANGUAGES CXX
)

if (${CMAKE_SIZEOF_VOID_P} EQUAL "8")
    set(STEEL_ARCHITECTURE "x64")
else()
    set(STEEL_ARCHITECTURE "x86")
endif ()

#if (MSVC)
#    if (NOT CMAKE_CL_64 AND NOT ${STEEL_ARCHITECTURE} EQUAL "x64")
#		message(FATAL_ERROR "\nError: Steel only supports Microsoft Visual Studio x64 for now.\n")
#	endif()
#endif ()

# Make Steel the Visual Studio Startup Project
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

# Support folders in IDE's
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Enable Steel macros:
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DSTEEL_DEBUG -DSTEEL_ENABLE_LOG")

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)
list(APPEND CMAKE_MODULE_PATH $ENV{CONDA_PREFIX}/Library/lib/cmake/Catch2)
string(REPLACE "\\" "/" CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}")

add_subdirectory(steel/src)
add_subdirectory(steel_tests)
add_subdirectory(third_party/flecs)
