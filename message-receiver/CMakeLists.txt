cmake_minimum_required(VERSION 3.16)
project(message-receiver LANGUAGES CXX DESCRIPTION "stonex cms client message receiver lib")

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 20)



file(GLOB sourceFiles 
	${PROJECT_SOURCE_DIR}/src/MessageReceiver/*.cpp  
	${PROJECT_SOURCE_DIR}/src/Configuration/*.cpp
	${PROJECT_SOURCE_DIR}/src/ConfigurationParser/*.cpp
	${PROJECT_SOURCE_DIR}/src/utils/*.cpp
	)
file(GLOB headerFiles 
	${PROJECT_SOURCE_DIR}/include/MessageReceiver/*.h 
	${PROJECT_SOURCE_DIR}/include/Configuration/*.h
	${PROJECT_SOURCE_DIR}/include/ConfigurationParser/*.h
	${PROJECT_SOURCE_DIR}/include/utils/*.h
	)


source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${sourceFiles} ${headerFiles})

add_library(message-receiver STATIC ${sourceFiles} ${headerFiles})              

target_include_directories(message-receiver PUBLIC ${PROJECT_SOURCE_DIR}/include )

target_link_libraries(
	message-receiver
	PRIVATE stonex-cms-amqp-wrapper
	PRIVATE message-content
	PRIVATE message-decorator
	PRIVATE test-utils
	PRIVATE message-content-verifier
	PRIVATE stonex-cms-amqp-test-notifier
	)

add_subdirectory(Test)
