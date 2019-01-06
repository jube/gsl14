cmake_minimum_required(VERSION 3.7)

project(GSL14
  VERSION 0.1.0
  LANGUAGES CXX C
)

find_package(Threads REQUIRED)

add_executable(gsl14_tests
  ${CMAKE_CURRENT_SOURCE_DIR}/vendor/googletest/googletest/src/gtest-all.cc
  tests/main.cc
  tests/test_assert.cc
  tests/test_util.cc
  tests/test_view.cc
)

target_include_directories(gsl14_tests
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/googletest/googletest/include
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/googletest/googletest
)

target_link_libraries(gsl14_tests
  Threads::Threads
)
