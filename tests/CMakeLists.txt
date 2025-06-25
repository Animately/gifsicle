cmake_minimum_required(VERSION 3.14)

set(TESTFILES
    main.cpp
    testutils.cpp
)

set(TEST_MAIN unit_tests)
set(TEST_RUNNER_PARAMS "")

add_executable(${TEST_MAIN} ${TESTFILES})
target_link_libraries(${TEST_MAIN} PRIVATE gifsiclelib doctest)
target_include_directories(${TEST_MAIN} PRIVATE ${GIFSICLELIB_FOLDER} ${GIFSICLE_INCLUDE})
set_target_properties(${TEST_MAIN} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

set_target_properties(${TEST_MAIN} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

add_test(
    NAME ${LIBRARY_NAME}.${TEST_MAIN}
    COMMAND ${TEST_MAIN} ${TEST_RUNNER_PARAMS})

set_tests_properties(${LIBRARY_NAME}.${TEST_MAIN} PROPERTIES
                     ENVIRONMENT
                     "TEST_DATA_DIR=${CMAKE_CURRENT_SOURCE_DIR}")
