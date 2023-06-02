cmake_minimum_required(VERSION 3.16)
project(message-receiver-test LANGUAGES CXX DESCRIPTION "stonex cms client message receiver lib tests")

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 20)


file(GLOB sourceFiles ${PROJECT_SOURCE_DIR}/*.cpp)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${sourceFiles})

add_executable(message-receiver-test main.cpp)              

target_include_directories(message-receiver-test PUBLIC ${PROJECT_SOURCE_DIR}/main.cpp )

target_link_libraries(message-receiver-test
	message-receiver
	message-content-verifier
	stonex-cms-amqp-wrapper
	CONAN_PKG::boost
	secur32 
	crypt32 
	Ws2_32
	)

configure_file(${PROJECT_SOURCE_DIR}/test_message_receiver.config ${CMAKE_CURRENT_BINARY_DIR}/test_message_receiver.config COPYONLY)

configure_file(${PROJECT_SOURCE_DIR}/test_message_counting_receiver.config ${CMAKE_CURRENT_BINARY_DIR}/test_message_counting_receiver.config COPYONLY)              
configure_file(${PROJECT_SOURCE_DIR}/test_message_receiver_to_file.config ${CMAKE_CURRENT_BINARY_DIR}/test_message_receiver_to_file.config COPYONLY)
configure_file(${PROJECT_SOURCE_DIR}/test_message_decorating_receiver.config ${CMAKE_CURRENT_BINARY_DIR}/test_message_decorating_receiver.config COPYONLY)

configure_file(${PROJECT_SOURCE_DIR}/test_message_counting_receiver_to_file.config ${CMAKE_CURRENT_BINARY_DIR}/test_message_counting_receiver_to_file.config COPYONLY)
configure_file(${PROJECT_SOURCE_DIR}/test_message_decorating_receiver_to_file.config ${CMAKE_CURRENT_BINARY_DIR}/test_message_decorating_receiver_to_file.config COPYONLY)
configure_file(${PROJECT_SOURCE_DIR}/test_message_decorating_counting_receiver.config ${CMAKE_CURRENT_BINARY_DIR}/test_message_decorating_counting_receiver.config COPYONLY)

configure_file(${PROJECT_SOURCE_DIR}/test_message_decorating_counting_receiver_to_file.config ${CMAKE_CURRENT_BINARY_DIR}/test_message_decorating_counting_receiver_to_file.config COPYONLY)

configure_file(${PROJECT_SOURCE_DIR}/test_message_receivers_all.config ${CMAKE_CURRENT_BINARY_DIR}/test_message_receivers_all.config COPYONLY)

configure_file(${PROJECT_SOURCE_DIR}/message_file.txt ${CMAKE_CURRENT_BINARY_DIR}/message_file.txt COPYONLY)


