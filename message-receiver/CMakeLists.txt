cmake_minimum_required(VERSION 3.16)
project(message-receiver LANGUAGES CXX DESCRIPTION "stonex cms client message receiver lib")

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 20)



file(GLOB sourceFiles 
	${PROJECT_SOURCE_DIR}/src/MessageReceiver/*.h 
	${PROJECT_SOURCE_DIR}/src/MessageReceiver/*.cpp  
	${PROJECT_SOURCE_DIR}/src/Configuration/*.h
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
  

          
if(BUILD_STATIC_LIBS)
	add_library(message-receiver STATIC)  
else()
	add_library(message-receiver SHARED)
endif()  


target_sources(message-receiver
    PRIVATE ${sourceFiles}
	PUBLIC ${headerFiles}
)

target_include_directories(message-receiver 
	PUBLIC ${PROJECT_SOURCE_DIR}/include
	PRIVATE ${PROJECT_SOURCE_DIR}/src
	)


target_link_libraries(
	message-receiver
	PUBLIC
	message-decorator
	test-utils
	stonex-cms-amqp-test-notifier
	message-content-verifier
	stonex-cms-amqp-wrapper
	PRIVATE 
	message-content
	)

add_subdirectory(Test)
