cmake_minimum_required(VERSION 3.16)
project(stonex-cms-amqp-message-receiver LANGUAGES CXX DESCRIPTION "stonex cms client test configuration")

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 20)



file(GLOB sourceFiles 
	${PROJECT_SOURCE_DIR}/src/MessageReceiver/*.cpp
	${PROJECT_SOURCE_DIR}/src/Configuration/*.cpp
	${PROJECT_SOURCE_DIR}/src/ConfigurationParser/*.cpp
	${PROJECT_SOURCE_DIR}/src/Listener/*.cpp
	${PROJECT_SOURCE_DIR}/src/Verifier/*.cpp
	)
file(GLOB headerFiles 
	${PROJECT_SOURCE_DIR}/include/MessageReceiver/*.h
	${PROJECT_SOURCE_DIR}/include/Configuration/*.h
	${PROJECT_SOURCE_DIR}/include/ConfigurationParser/*.h
	${PROJECT_SOURCE_DIR}/include/Listener/*.h
	${PROJECT_SOURCE_DIR}/include/Verifier/*.h	
	)


source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${sourceFiles} ${headerFiles})

add_library(stonex-cms-amqp-message-receiver STATIC ${sourceFiles} ${headerFiles})              

target_include_directories(stonex-cms-amqp-message-receiver 
	PUBLIC ${PROJECT_SOURCE_DIR}/include
	)

target_link_libraries(stonex-cms-amqp-message-receiver
	apache-cms-interface
	stonex-cms-amqp-wrapper
#	stonex-cms-amqp-test-verifier
	stonex-cms-amqp-test-notifier
	)

	add_subdirectory(Test)