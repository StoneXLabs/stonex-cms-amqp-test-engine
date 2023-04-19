cmake_minimum_required(VERSION 3.16)
project(stonex-cms-amqp-test LANGUAGES CXX DESCRIPTION "stonex cms client test configuration")
#include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
#conan_basic_setup(TARGETS)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 20)


file(GLOB sourceFiles ${PROJECT_SOURCE_DIR}/TestSuite/*.cpp )
file(GLOB headerFiles ${PROJECT_SOURCE_DIR}/TestSuite/*.h)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${sourceFiles} ${headerFiles})

add_library(stonex-cms-amqp-test STATIC ${sourceFiles} ${headerFiles})              

target_include_directories(stonex-cms-amqp-test PUBLIC ${PROJECT_SOURCE_DIR})

##target_link_libraries(stonex-cms-amqp-test stonex-cms-amqp-test-configuration-parser  stonex-cms-amqp-wrapper stonex-cms-amqp-message-receiver stonex-cms-amqp-message-sender stonex-cms-amqp-test-raport)


#target_link_libraries(stonex-cms-amqp-test stonex-cms-amqp-test-engine stonex-cms-amqp-message-receiver stonex-cms-amqp-message-sender stonex-cms-amqp-test-raport)
target_link_libraries(stonex-cms-amqp-test stonex-cms-amqp-test-engine)