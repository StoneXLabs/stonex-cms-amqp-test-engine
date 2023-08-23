cmake_minimum_required(VERSION 3.16)
project(stonex-cms-amqp-wrapper LANGUAGES CXX DESCRIPTION "stonex cms amqp client wrapper lib")

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 20)


file(GLOB sourceFiles ${PROJECT_SOURCE_DIR}/src/Wrapper/*.cpp  ${PROJECT_SOURCE_DIR}/src/Configuration/*.cpp ${PROJECT_SOURCE_DIR}/src/ConfigurationParser/*.cpp)

file(GLOB headerFiles ${PROJECT_SOURCE_DIR}/include/Configuration/*.h  ${PROJECT_SOURCE_DIR}/include/Wrapper/*.h ${PROJECT_SOURCE_DIR}/include/ConfigurationParser/*.h)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${sourceFiles} ${headerFiles})
          

          
if(BUILD_STATIC_LIBS)
	add_library(stonex-cms-amqp-wrapper STATIC ${sourceFiles} ${headerFiles})    
else()
	add_library(stonex-cms-amqp-wrapper SHARED ${sourceFiles} ${headerFiles})
endif()  


target_include_directories(stonex-cms-amqp-wrapper PUBLIC ${PROJECT_SOURCE_DIR}/include/ )

target_link_libraries(stonex-cms-amqp-wrapper 
	INTERFACE
	apache-cms-interface
	PUBLIC
	test-utils
	CONAN_PKG::boost
	CONAN_PKG::stonex-logger-wrapper
	PRIVATE	
	CONAN_PKG::stonex-cms-amqp-lib
	)

add_subdirectory(Test)
