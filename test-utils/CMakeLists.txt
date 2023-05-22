cmake_minimum_required(VERSION 3.16)
project(test-utils LANGUAGES CXX DESCRIPTION "stonex cms client test engine utils")

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 20)



file(GLOB sourceFiles 
	${PROJECT_SOURCE_DIR}/src/utils/*.cpp  
	)
file(GLOB headerFiles 
	${PROJECT_SOURCE_DIR}/include/utils/*.h 
	)


source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${sourceFiles} ${headerFiles})

add_library(test-utils STATIC ${sourceFiles} ${headerFiles})              

target_include_directories(test-utils PUBLIC ${PROJECT_SOURCE_DIR}/include )


target_link_libraries(test-utils PUBLIC apache-cms-interface)
	