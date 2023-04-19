
cmake_minimum_required(VERSION 3.16)
project(stonex-cms-amqp-test-engine LANGUAGES CXX DESCRIPTION "stonex cms client test engine")
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 20)


add_subdirectory(CMSClientWrapper)
add_subdirectory(common)
add_subdirectory(Configuration)
add_subdirectory(ConfigurationParser)
add_subdirectory(MessageContent)
add_subdirectory(MessageContentVerifiers)
add_subdirectory(MessageReceiver)
add_subdirectory(MessageSender)
add_subdirectory(stonex-cms-amqp-test-engine)
add_subdirectory(TestEventHandler)
add_subdirectory(Verifier)
add_subdirectory(TestNotifier)




