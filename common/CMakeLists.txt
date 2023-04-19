cmake_minimum_required(VERSION 3.16)
project(apache-cms-interface LANGUAGES CXX DESCRIPTION "Apache cms interface")

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 20)


add_library(apache-cms-interface INTERFACE)              

target_include_directories(apache-cms-interface
	INTERFACE ${PROJECT_SOURCE_DIR}/activemq-cpp/src/main
)

