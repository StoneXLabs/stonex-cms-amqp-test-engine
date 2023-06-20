cmake_minimum_required(VERSION 3.16)
project(message-sender-test LANGUAGES CXX DESCRIPTION "stonex cms client message sender lib tests")

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 20)


file(GLOB sourceFiles ${PROJECT_SOURCE_DIR}/*.cpp ${PROJECT_SOURCE_DIR}/test_utils/*.cpp)
file(GLOB headerFiles ${PROJECT_SOURCE_DIR}/test_utils/*.h)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${sourceFiles})

add_executable(message-sender-test main.cpp)              

target_include_directories(message-sender-test PUBLIC ${PROJECT_SOURCE_DIR} )

target_link_libraries(message-sender-test
	message-sender
	stonex-cms-amqp-wrapper
	message-decorator
	CONAN_PKG::boost
	secur32 
	crypt32 
	Ws2_32
	)

configure_file(${PROJECT_SOURCE_DIR}/test_message_sender.config ${CMAKE_CURRENT_BINARY_DIR}/test_message_sender.config COPYONLY)

configure_file(${PROJECT_SOURCE_DIR}/test_message_counting_sender.config ${CMAKE_CURRENT_BINARY_DIR}/test_message_counting_sender.config COPYONLY)              
configure_file(${PROJECT_SOURCE_DIR}/test_message_sender_from_file.config ${CMAKE_CURRENT_BINARY_DIR}/test_message_sender_from_file.config COPYONLY)
configure_file(${PROJECT_SOURCE_DIR}/test_message_decorating_sender.config ${CMAKE_CURRENT_BINARY_DIR}/test_message_decorating_sender.config COPYONLY)

configure_file(${PROJECT_SOURCE_DIR}/test_message_counting_sender_from_file.config ${CMAKE_CURRENT_BINARY_DIR}/test_message_counting_sender_from_file.config COPYONLY)
configure_file(${PROJECT_SOURCE_DIR}/test_message_decorating_sender_from_file.config ${CMAKE_CURRENT_BINARY_DIR}/test_message_decorating_sender_from_file.config COPYONLY)
configure_file(${PROJECT_SOURCE_DIR}/test_message_decorating_counting_sender.config ${CMAKE_CURRENT_BINARY_DIR}/test_message_decorating_counting_sender.config COPYONLY)

configure_file(${PROJECT_SOURCE_DIR}/test_message_decorating_counting_sender_from_file.config ${CMAKE_CURRENT_BINARY_DIR}/test_message_decorating_counting_sender_from_file.config COPYONLY)

configure_file(${PROJECT_SOURCE_DIR}/test_message_senders_all.config ${CMAKE_CURRENT_BINARY_DIR}/test_message_senders_all.config COPYONLY)

configure_file(${PROJECT_SOURCE_DIR}/message_file.txt ${CMAKE_CURRENT_BINARY_DIR}/message_file.txt COPYONLY)


