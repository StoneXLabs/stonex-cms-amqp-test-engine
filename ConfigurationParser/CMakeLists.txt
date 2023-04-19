cmake_minimum_required(VERSION 3.16)
project(stonex-cms-amqp-test-configuration-parser LANGUAGES CXX DESCRIPTION "stonex cms client test configuration parser interface")

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 20)

file(GLOB headerFiles ${PROJECT_SOURCE_DIR}/include/ConfigurationParser/*.h )

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES  ${headerFiles})

add_library(stonex-cms-amqp-test-configuration-parser INTERFACE)              

target_include_directories(stonex-cms-amqp-test-configuration-parser
	INTERFACE ${PROJECT_SOURCE_DIR}/include 
)

