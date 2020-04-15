# CMAKE_PREFIX_PATH: list of directories specifying installation prefixes to be searched by 
# the find_package(), find_program(), find_library(), find_file(), and find_path() commands.
list(APPEND CMAKE_PREFIX_PATH $ENV{CONDA_PREFIX}/Library)
string(REPLACE "\\" "/" CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH}")
message(STATUS ">>>> Current CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS ">>>> CMake search paths: ${CMAKE_PREFIX_PATH}")

find_package(Threads REQUIRED)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_gfx REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(spdlog REQUIRED)

message(STATUS ">>>> SDL2_INCLUDE_DIR: ${SDL2_INCLUDE_DIR}")
message(STATUS ">>>> SDL2_LIBRARY: ${SDL2_LIBRARY}")

set(STEEL_INCLUDE_DIR "../include/")
string(REPLACE "\\" "/" STEEL_INCLUDE_DIR "${STEEL_INCLUDE_DIR}")

set(SOURCE_FILES
	engine.cpp
	game.cpp
	game_info.cpp
	log.cpp
	renderer.cpp
)

set(HEADER_LIST 
	"${STEEL_INCLUDE_DIR}steel.hpp"
	"${STEEL_INCLUDE_DIR}core.hpp"
	"${STEEL_INCLUDE_DIR}engine.hpp"
	"${STEEL_INCLUDE_DIR}game.hpp"
	"${STEEL_INCLUDE_DIR}game_info.hpp"
	"${STEEL_INCLUDE_DIR}log.hpp"
	"${STEEL_INCLUDE_DIR}renderer.hpp"
)

# Build Steel as a library 
add_library(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_LIST})
# We need this directory, and users of our library will need it too
target_include_directories(${PROJECT_NAME} PUBLIC ${STEEL_INCLUDE_DIR})

message(STATUS ">>>> CMake executables: ${SOURCE_FILES}")

# Note that library project should link to SDL2::Core, application project should link to SDL2::Main
target_link_libraries(${PROJECT_NAME} PUBLIC SDL2::Core SDL2::Image SDL2::GFX SDL2::Mixer SDL2::TTF spdlog::spdlog)

set_target_properties(
	${PROJECT_NAME} PROPERTIES
	LINK_FLAGS /SUBSYSTEM:CONSOLE
	ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin/debug"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin/release"
)