
project(tests)

enable_testing()

add_executable(${PROJECT_NAME}
  unit_tests_main.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(${PROJECT_NAME} 
    core
    gtest
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})
