cmake_minimum_required(VERSION 3.16)
project(stonex-cms-amqp-wrapper-test LANGUAGES CXX DESCRIPTION "stonex cms amqp client wrapper lib tests")

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 20)


file(GLOB sourceFiles ${PROJECT_SOURCE_DIR}/*.cpp)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${sourceFiles})

add_executable(stonex-cms-amqp-wrapper-test main.cpp)              

target_include_directories(stonex-cms-amqp-wrapper-test PUBLIC ${PROJECT_SOURCE_DIR}/main.cpp )

target_link_libraries(stonex-cms-amqp-wrapper-test
	stonex-cms-amqp-wrapper
	CONAN_PKG::stonex-cms-amqp-lib
	CONAN_PKG::stonex-logger-wrapper
	CONAN_PKG::boost
	secur32 
	crypt32 
	Ws2_32
	)


configure_file(${PROJECT_SOURCE_DIR}/test_consumer.config ${CMAKE_CURRENT_BINARY_DIR}/test_consumer.config COPYONLY)
configure_file(${PROJECT_SOURCE_DIR}/test_producer.config ${CMAKE_CURRENT_BINARY_DIR}/test_producer.config COPYONLY)
configure_file(${PROJECT_SOURCE_DIR}/test_session.config ${CMAKE_CURRENT_BINARY_DIR}/test_session.config COPYONLY)
configure_file(${PROJECT_SOURCE_DIR}/test_connection.config ${CMAKE_CURRENT_BINARY_DIR}/test_connection.config COPYONLY)
configure_file(${PROJECT_SOURCE_DIR}/test_wrapper.config ${CMAKE_CURRENT_BINARY_DIR}/test_wrapper.config COPYONLY)