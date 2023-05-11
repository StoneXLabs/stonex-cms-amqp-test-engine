cmake_minimum_required(VERSION 3.16)
project(stonex-cms-amqp-send-receive-test LANGUAGES CXX DESCRIPTION "stonex cms client test configuration")

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 20)



file(GLOB sourceFiles 
	${PROJECT_SOURCE_DIR}/*.cpp
	)
file(GLOB headerFiles 
	${PROJECT_SOURCE_DIR}/*.h	
	)


source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${sourceFiles} ${headerFiles})

add_executable(stonex-cms-amqp-send-receive-test ${sourceFiles} ${headerFiles})              

target_include_directories(stonex-cms-amqp-send-receive-test 
	PUBLIC ${PROJECT_SOURCE_DIR}/include
	)

target_link_libraries(stonex-cms-amqp-send-receive-test
	stonex-cms-amqp-message-receiver
	stonex-cms-amqp-message-sender
	secur32 
	crypt32 
	Ws2_32
	)