cmake_minimum_required(VERSION 3.20)

project(serialize-buffer)

set(CMAKE_C_STANDARD 11)
set(LIB_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/serialize_buffer.c"
)
add_library(serialize-buffer
    STATIC
        ${LIB_SOURCES}
)
target_include_directories(serialize-buffer
    PUBLIC
        inc
)

# Unit Test
option(ENABLE_UNIT_TESTS "Download test framework and build test executable" OFF)
if (ENABLE_UNIT_TESTS)
    if(EXISTS ${CMAKE_CURRENT_BINARY_DIR}/conaninfo.txt)
        list(PREPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_BINARY_DIR}")
    endif()
    find_package(GTest 1.10.0 REQUIRED COMPONENTS)
    enable_testing()

    set(TEST_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/tests/main.cpp"
        )
    add_executable(serialize-buffer-tests ${TEST_SOURCES})
    target_compile_features(serialize-buffer-tests
        PRIVATE
            cxx_std_17
        )
    target_link_libraries(serialize-buffer-tests
        PRIVATE
            serialize-buffer
            GTest::GTest
    )
    add_test(
        NAME serialize-buffer-tests
        COMMAND $<TARGET_FILE:serialize-buffer-tests>
    )
ENDIF()
