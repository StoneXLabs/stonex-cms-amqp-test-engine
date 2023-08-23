cmake_minimum_required(VERSION 3.16)
project(message-sender LANGUAGES CXX DESCRIPTION "stonex cms client message sender lib")

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 20)



file(GLOB sourceFiles 
	${PROJECT_SOURCE_DIR}/src/MessageSender/*.h  
	${PROJECT_SOURCE_DIR}/src/MessageSender/*.cpp  
	${PROJECT_SOURCE_DIR}/src/Configuration/*.cpp
	${PROJECT_SOURCE_DIR}/src/ConfigurationParser/*.cpp
	${PROJECT_SOURCE_DIR}/src/utils/*.cpp
	)
file(GLOB headerFiles 
	${PROJECT_SOURCE_DIR}/include/MessageSender/*.h 
	${PROJECT_SOURCE_DIR}/include/Configuration/*.h
	${PROJECT_SOURCE_DIR}/include/ConfigurationParser/*.h
	${PROJECT_SOURCE_DIR}/include/utils/*.h
	)


source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${sourceFiles} ${headerFiles})

          
if(BUILD_STATIC_LIBS)
	add_library(message-sender STATIC)    
else()
	add_library(message-sender SHARED) 
endif()  


target_sources(message-sender
    PRIVATE ${sourceFiles}
	PUBLIC ${headerFiles}
	)

target_include_directories(message-sender 
	PUBLIC ${PROJECT_SOURCE_DIR}/include
	PRIVATE ${PROJECT_SOURCE_DIR}/src
	)              
	
target_link_libraries(
	message-sender
	PUBLIC
	stonex-cms-amqp-test-notifier
	stonex-cms-amqp-wrapper
	test-utils
	PRIVATE
	message-content
	message-decorator
	)

add_subdirectory(Test)
