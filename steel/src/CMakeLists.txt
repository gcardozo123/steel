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

message(STATUS ">>>> SDL2_INCLUDE_DIR: ${SDL2_INCLUDE_DIR}")
message(STATUS ">>>> SDL2_LIBRARY: ${SDL2_LIBRARY}")

set(SOURCE_FILES
    main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

message(STATUS ">>>> CMake executables: ${SOURCE_FILES}")

# Note that library project should link to SDL2::Core, application project should link to SDL2::Main
target_link_libraries(${PROJECT_NAME} PUBLIC SDL2::Main SDL2::Image SDL2::GFX SDL2::Mixer SDL2::TTF)

set_target_properties(
	${PROJECT_NAME} PROPERTIES
	LINK_FLAGS /SUBSYSTEM:CONSOLE
	ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin/debug"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin/release"
)