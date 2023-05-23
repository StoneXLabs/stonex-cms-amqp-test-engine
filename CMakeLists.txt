
cmake_minimum_required(VERSION 3.16)
project(stonex-cms-amqp-test-engine LANGUAGES CXX DESCRIPTION "stonex cms client test engine")
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(common)
add_subdirectory(stonex-cms-amqp-test-engine)
add_subdirectory(stonex-cms-amqp-wrapper)
add_subdirectory(test-utils)
add_subdirectory(message-sender)
add_subdirectory(message-receiver)
add_subdirectory(message-content)
add_subdirectory(message-decorator)
add_subdirectory(message-content-verifier)
add_subdirectory(stonex-cms-amqp-test-notifier)


#add_subdirectory(Testers)




