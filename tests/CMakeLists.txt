include(GoogleTest)

file(GLOB_RECURSE
    TEST_SOURCES
    RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    gtest-*.cc
    gtest-*.cpp
)

foreach(TEST_SOURCE IN LISTS TEST_SOURCES)
    get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WLE)
    add_executable(${TEST_NAME})
    target_sources(${TEST_NAME} PRIVATE ${TEST_SOURCE})
    target_link_libraries(${TEST_NAME} PRIVATE GTest::gtest_main)
    target_link_libraries(${TEST_NAME} PRIVATE beidou_grid)
    gtest_add_tests(TARGET ${TEST_NAME})
endforeach()
