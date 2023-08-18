
cmake_minimum_required(VERSION 3.16)
project(stonex-cms-amqp-test-engine LANGUAGES CXX DESCRIPTION "stonex cms client test engine lib")

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 20)

file(GLOB sourceFiles 
	${PROJECT_SOURCE_DIR}/src/Configuration/*.cpp
	${PROJECT_SOURCE_DIR}/src/ConfigurationParser/*.cpp 
	${PROJECT_SOURCE_DIR}/src/TestSuite/*.cpp
	${PROJECT_SOURCE_DIR}/src/utils/*.cpp
	)

file(GLOB headerFiles 
	${PROJECT_SOURCE_DIR}/include/Configuration/*.h 
	${PROJECT_SOURCE_DIR}/include/ConfigurationParser/*.h 
	${PROJECT_SOURCE_DIR}/include/TestSuite/*.h
	${PROJECT_SOURCE_DIR}/include/utils/*.h
	)


source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${sourceFiles} ${headerFiles}  )

add_library(stonex-cms-amqp-test-engine STATIC ${sourceFiles} ${headerFiles})     


target_include_directories(stonex-cms-amqp-test-engine
	PUBLIC ${PROJECT_SOURCE_DIR}/include 
	PUBLIC ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(stonex-cms-amqp-test-engine 
	INTERFACE	
	apache-cms-interface
	PUBLIC
	message-receiver
	message-sender
	PRIVATE
	stonex-cms-amqp-test-notifier
	CONAN_PKG::fmt
	CONAN_PKG::boost
	)

#	add_subdirectory(Test)
