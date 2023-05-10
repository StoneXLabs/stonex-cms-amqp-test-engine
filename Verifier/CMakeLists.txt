cmake_minimum_required(VERSION 3.16)
project(stonex-cms-amqp-test-verifier LANGUAGES CXX DESCRIPTION "stonex cms client test configuration")
#include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
#conan_basic_setup(TARGETS)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 20)



file(GLOB sourceFiles ${PROJECT_SOURCE_DIR}/src/Verifier/*.cpp )
file(GLOB headerFiles ${PROJECT_SOURCE_DIR}/include/Verifier/*.h)


source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${sourceFiles} ${headerFiles})

add_library(stonex-cms-amqp-test-verifier STATIC ${sourceFiles} ${headerFiles})              

target_include_directories(stonex-cms-amqp-test-verifier 
PUBLIC ${PROJECT_SOURCE_DIR}/include/
PRIVATE ${PROJECT_SOURCE_DIR}/src/
)


target_link_libraries(stonex-cms-amqp-test-verifier 
	apache-cms-interface
	stonex-cms-amqp-event-handler
	stonex-cms-amqp-message-content-verifier
	)

