cmake_minimum_required(VERSION 3.16)
project(stonex-cms-amqp-event-handler LANGUAGES CXX DESCRIPTION "stonex cms client test configuration")
#include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
#conan_basic_setup(TARGETS)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 20)



file(GLOB sourceFiles 
	${PROJECT_SOURCE_DIR}/src/TestEventWrapper/*.cpp
	${PROJECT_SOURCE_DIR}/src/TestEventListener/*.cpp
	${PROJECT_SOURCE_DIR}/src/TestEventListenerFactory/*.cpp
)

file(GLOB headerFiles 
	${PROJECT_SOURCE_DIR}/include/TestEventWrapper/*.h
	${PROJECT_SOURCE_DIR}/include/TestEventWrapperFactory/*.h
	${PROJECT_SOURCE_DIR}/include/TestEventListener/*.h
	${PROJECT_SOURCE_DIR}/include/TestEventListenerFactory/*.h
	
	)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${sourceFiles} ${headerFiles})

add_library(stonex-cms-amqp-event-handler STATIC ${sourceFiles} ${headerFiles})              

target_include_directories(stonex-cms-amqp-event-handler
#	INTERFACE ${PROJECT_SOURCE_DIR}/include
	PUBLIC ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(stonex-cms-amqp-event-handler PUBLIC apache-cms-interface stonex-cms-amqp-test-notifier)
