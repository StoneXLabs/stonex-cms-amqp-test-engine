cmake_minimum_required(VERSION 3.16)
project(test-case-performer LANGUAGES CXX DESCRIPTION "stonex cms client test configuration")

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 20)


file(GLOB sourceFiles 
	${PROJECT_SOURCE_DIR}/src/Configuration/*.cpp
	${PROJECT_SOURCE_DIR}/src/MessageSender/*.cpp
	${PROJECT_SOURCE_DIR}/src/MessageReceiver/*.cpp
)

file(GLOB headerFiles 
	${PROJECT_SOURCE_DIR}/include/Configuration/*.h
	${PROJECT_SOURCE_DIR}/include/MessageSender/*.h
	${PROJECT_SOURCE_DIR}/include/MessageReceiver/*.h
	)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${sourceFiles} ${headerFiles})

add_library(test-case-performer STATIC ${sourceFiles} ${headerFiles})              

target_include_directories(test-case-performer PUBLIC ${PROJECT_SOURCE_DIR}/include/ )


target_link_libraries(test-case-performer 
	stonex-cms-amqp-wrapper
	)