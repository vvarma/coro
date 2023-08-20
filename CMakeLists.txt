cmake_minimum_required(VERSION 3.25)
project(coro VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
include(cmake/options.cmake)
include(cmake/dependencies.cmake)

FILE(GLOB SOURCES src/*.cpp)
add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

if (ENABLE_TESTS)
  include(CTest)
  FILE(GLOB TEST_SOURCES test/*.cpp)
  add_executable(${PROJECT_NAME}_tests ${TEST_SOURCES})
  target_link_libraries(${PROJECT_NAME}_tests PRIVATE ${PROJECT_NAME} doctest::doctest)
  add_test(NAME ${PROJECT_NAME}_tests COMMAND ${PROJECT_NAME}_tests -m)
endif()
