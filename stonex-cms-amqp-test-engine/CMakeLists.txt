
cmake_minimum_required(VERSION 3.16)
project(stonex-cms-amqp-test-engine LANGUAGES CXX DESCRIPTION "stonex cms client test engine")
#include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
#conan_basic_setup(TARGETS)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 20)

file(GLOB sourceFiles 
	${PROJECT_SOURCE_DIR}/src/Configuration/*.cpp
	${PROJECT_SOURCE_DIR}/src/ConfigurationParser/*.cpp 
#	${PROJECT_SOURCE_DIR}/src/TestEventHandler/*.cpp
#	${PROJECT_SOURCE_DIR}/src/Listener/*.cpp
#	${PROJECT_SOURCE_DIR}/src/MessageSource/*.cpp
#	${PROJECT_SOURCE_DIR}/src/VerifyingReceiverFactory/*.cpp
#	${PROJECT_SOURCE_DIR}/src/TestEventWrapperFactory/*.cpp
#	${PROJECT_SOURCE_DIR}/src/TestSuite/*.cpp
	)

file(GLOB headerFiles 
	${PROJECT_SOURCE_DIR}/include/Configuration/*.h 
	${PROJECT_SOURCE_DIR}/include/ConfigurationParser/*.h 
#	${PROJECT_SOURCE_DIR}/include/TestEventHandler/*.h 
#	${PROJECT_SOURCE_DIR}/include/Listener/*.h
#	${PROJECT_SOURCE_DIR}/include/MessageSource/*.h
#	${PROJECT_SOURCE_DIR}/include/VerifyingReceiverFactory/*.h
#	${PROJECT_SOURCE_DIR}/include/TestEventWrapperFactory/*.h
#	${PROJECT_SOURCE_DIR}/include/TestSuite/*.h
	)


source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${sourceFiles} ${headerFiles}  )

add_library(stonex-cms-amqp-test-engine STATIC ${sourceFiles} ${headerFiles})     


target_include_directories(stonex-cms-amqp-test-engine
	PUBLIC ${PROJECT_SOURCE_DIR}/include 
	PUBLIC ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(stonex-cms-amqp-test-engine 
	apache-cms-interface
	stonex-cms-amqp-event-handler
	stonex-cms-amqp-test-verifier
	stonex-cms-amqp-wrapper
	stonex-cms-amqp-message-receiver
	stonex-cms-amqp-message-sender
	stonex-cms-amqp-test-notifier
	CONAN_PKG::boost
	)

	add_subdirectory(Test)