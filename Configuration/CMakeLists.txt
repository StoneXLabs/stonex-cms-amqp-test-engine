cmake_minimum_required(VERSION 3.16)
project(stonex-cms-amqp-test-configuration LANGUAGES CXX DESCRIPTION "stonex cms client test configuration")

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 20)


file(GLOB sourceFiles ${PROJECT_SOURCE_DIR}/src/Configuration/*.cpp)
file(GLOB headerFiles ${PROJECT_SOURCE_DIR}/src/Configuration/*.h ${PROJECT_SOURCE_DIR}/include/Configuration/*.h )

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${sourceFiles} ${headerFiles})

add_library(stonex-cms-amqp-test-configuration STATIC ${sourceFiles} ${headerFiles})              

target_include_directories(stonex-cms-amqp-test-configuration
	PUBLIC ${PROJECT_SOURCE_DIR}/include 
	PRIVATE ${PROJECT_SOURCE_DIR}/src
)

