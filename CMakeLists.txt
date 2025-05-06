cmake_minimum_required(VERSION 3.14)
project(mini_front_end_llvm VERSION 0.1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

# Create library target without main()
add_library(minimal_fe_lib OBJECT
  src/minimal_fe.cc
)

target_compile_definitions(minimal_fe_lib PRIVATE TESTING=1)

target_include_directories(minimal_fe_lib PUBLIC
  ${CMAKE_SOURCE_DIR}/src
)

# Main executable
add_executable(minimal_fe src/minimal_fe.cc)

# Test executable
add_executable(minimal_fe_test
  test/lexer_test.cc
  test/parser_test.cc
  test/ast_test.cc
  $<TARGET_OBJECTS:minimal_fe_lib>
)

target_link_libraries(minimal_fe_test
  GTest::gtest_main
  GTest::gmock_main
)

# Include directories
target_include_directories(minimal_fe_test PRIVATE
  ${CMAKE_SOURCE_DIR}/src
)

# Enable testing
enable_testing()
add_test(NAME minimal_fe_test COMMAND minimal_fe_test)