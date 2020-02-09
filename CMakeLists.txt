CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

# issue [https://gitlab.kitware.com/cmake/cmake/issues/19409] does not allow to do this:
#set(CMAKE_GENERATOR_PLATFORM "Visual Studio 15 2017 Win64")
# it's necessary to run with: cmake -G "Visual Studio 15 2017 Win64" ..

project(steel)

list(APPEND CMAKE_PREFIX_PATH $ENV{CONDA_PREFIX}/Library/lib)
list(APPEND CMAKE_PREFIX_PATH $ENV{CONDA_PREFIX}/Library/include)
list(APPEND CMAKE_PREFIX_PATH ${PROJECT_SOURCE_DIR}/source/cpp/include)

message(STATUS ">>>> CMake search paths: ${CMAKE_PREFIX_PATH}")

find_path(
	SDL2_INCLUDE_DIR
	SDL.h
    PATH_SUFFIXES SDL2
)
find_library(
	SDL2_LIBRARY
	NAMES SDL2
    PATH_SUFFIXES lib64 lib lib/x64
)

message(STATUS ">>>> SDL2_INCLUDE_DIR: ${SDL2_INCLUDE_DIR}")
message(STATUS ">>>> SDL2_LIBRARY: ${SDL2_LIBRARY}")

file(GLOB_RECURSE SOURCE_FILES "source/cpp/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
target_sources(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/source/cpp/main.cpp)

message(STATUS ">>>> CMake executables: ${SOURCE_FILES}")

target_include_directories(${PROJECT_NAME} PUBLIC ${SDL2_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC ${SDL2_LIBRARY})
set_target_properties(
	${PROJECT_NAME} PROPERTIES
	LINK_FLAGS /SUBSYSTEM:CONSOLE
)