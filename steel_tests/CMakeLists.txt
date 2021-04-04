find_package(Catch2 REQUIRED)

set(UNIT_TEST_SOURCE_LIST
  test_game.cpp
  test_log.cpp
  test_vector2.cpp
)

set(TARGET_NAME tests)

add_executable(${TARGET_NAME}
  main.cpp
  ${UNIT_TEST_SOURCE_LIST})

target_link_libraries(${TARGET_NAME} PRIVATE steel Catch2::Catch2)  

add_test(
  NAME ${TARGET_NAME}
  COMMAND ${TARGET_NAME} -o report.xml -r junit
)