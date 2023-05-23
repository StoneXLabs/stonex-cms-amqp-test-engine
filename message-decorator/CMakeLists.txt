cmake_minimum_required(VERSION 3.16)
project(message-decorator LANGUAGES CXX DESCRIPTION "stonex cms client message decorator lib")

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 20)



file(GLOB sourceFiles 
	${PROJECT_SOURCE_DIR}/src/MessageDecorator/*.cpp
	${PROJECT_SOURCE_DIR}/src/MessageDecorator/*.h
	${PROJECT_SOURCE_DIR}/src/Configuration/*.cpp
	${PROJECT_SOURCE_DIR}/src/ConfigurationParser/*.cpp
	)
file(GLOB headerFiles 
	${PROJECT_SOURCE_DIR}/include/MessageDecorator/*.h
	${PROJECT_SOURCE_DIR}/include/Configuration/*.h
	${PROJECT_SOURCE_DIR}/include/ConfigurationParser/*.h
	)


source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${sourceFiles} ${headerFiles})

add_library(message-decorator STATIC)    

target_sources(message-decorator
    PRIVATE ${sourceFiles}
	PUBLIC ${headerFiles}
)

target_include_directories(message-decorator 
	PUBLIC ${PROJECT_SOURCE_DIR}/include
	PRIVATE ${PROJECT_SOURCE_DIR}/src
	)

target_link_libraries(message-decorator
	PUBLIC apache-cms-interface
	PUBLIC message-content
	PRIVATE stonex-cms-amqp-wrapper
	)

add_subdirectory(Test)