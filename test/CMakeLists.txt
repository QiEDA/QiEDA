add_executable(
    rogerber_tests
    rogerber/main.cpp
    rogerber/TestCoordinateConverter.cpp
    )

add_dependencies(rogerber_tests gtest rogerber)

target_link_libraries(
    rogerber_tests
    rogerber
    gtest
    )

include(CTest)
enable_testing()

add_test(rogerber ${PROJECT_BINARY_DIR}/rogerber_tests)