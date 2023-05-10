cmake_minimum_required(VERSION 3.16)
project(stonex-cms-amqp-message-sender LANGUAGES CXX DESCRIPTION "stonex cms client test configuration")
#include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
#conan_basic_setup(TARGETS)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 20)



file(GLOB sourceFiles ${PROJECT_SOURCE_DIR}/src/MessageSender/*.cpp  ${PROJECT_SOURCE_DIR}/src/Configuration/*.cpp)
file(GLOB headerFiles ${PROJECT_SOURCE_DIR}/include/MessageSender/*.h ${PROJECT_SOURCE_DIR}/include/Configuration/*.h)


source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${sourceFiles} ${headerFiles})

add_library(stonex-cms-amqp-message-sender STATIC ${sourceFiles} ${headerFiles})              

target_include_directories(stonex-cms-amqp-message-sender PUBLIC ${PROJECT_SOURCE_DIR}/include )

target_link_libraries(
	stonex-cms-amqp-message-sender
	stonex-cms-amqp-wrapper
	stonex-cms-amqp-test-verifier
	stonex-cms-amqp-test-notifier
	)
