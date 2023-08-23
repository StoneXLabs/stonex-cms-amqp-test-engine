cmake_minimum_required(VERSION 3.16)
project(message-content LANGUAGES CXX DESCRIPTION "stonex cms client message content lib")

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 20)


file(GLOB sourceFiles 
	${PROJECT_SOURCE_DIR}/src/MessageContent/*.cpp 
	${PROJECT_SOURCE_DIR}/src/MessageContent/*.h 
	${PROJECT_SOURCE_DIR}/src/ConfigurationParser/*.h 
	${PROJECT_SOURCE_DIR}/src/ConfigurationParser/*.cpp 
	)
file(GLOB headerFiles 
	${PROJECT_SOURCE_DIR}/include/MessageContent/*.h 
	${PROJECT_SOURCE_DIR}/include/ConfigurationParser/*.h
	)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${sourceFiles} ${headerFiles})
    

          
if(BUILD_STATIC_LIBS)
	add_library(message-content STATIC)  
else()
	add_library(message-content SHARED)  
endif()  


target_sources(message-content
    PRIVATE ${sourceFiles}
	PUBLIC ${headerFiles}
)

target_include_directories(message-content 
	PUBLIC ${PROJECT_SOURCE_DIR}/include
	PRIVATE ${PROJECT_SOURCE_DIR}/src
	)

target_link_libraries(message-content  PRIVATE CONAN_PKG::boost)

add_subdirectory(Test)
