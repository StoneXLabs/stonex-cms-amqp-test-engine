cmake_minimum_required(VERSION 3.16)
project(stonex-cms-amqp-test-engne-test LANGUAGES CXX DESCRIPTION "stonex cms client test engine lib tests")

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 20)


file(GLOB sourceFiles ${PROJECT_SOURCE_DIR}/*.cpp ${PROJECT_SOURCE_DIR}/test_utils/*cpp)
file(GLOB headerFiles ${PROJECT_SOURCE_DIR}/*.h ${PROJECT_SOURCE_DIR}/test_utils/*h)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${sourceFiles} ${headerFiles})

add_executable(stonex-cms-amqp-test-engne-test main.cpp ${sourceFiles} ${headerFiles})              

target_include_directories(stonex-cms-amqp-test-engne-test PUBLIC ${PROJECT_SOURCE_DIR} )

target_link_libraries(stonex-cms-amqp-test-engne-test
	stonex-cms-amqp-test-engine
	message-receiver
	message-sender
	CONAN_PKG::boost
	secur32 
	crypt32 
	Ws2_32
	)

	
configure_file(${PROJECT_SOURCE_DIR}/test_suite.config ${CMAKE_CURRENT_BINARY_DIR}/test_suite.config COPYONLY)    
configure_file(${PROJECT_SOURCE_DIR}/test_case.config ${CMAKE_CURRENT_BINARY_DIR}/test_case.config COPYONLY)     
configure_file(${PROJECT_SOURCE_DIR}/test_case_all.config ${CMAKE_CURRENT_BINARY_DIR}/test_case_all.config COPYONLY)    
configure_file(${PROJECT_SOURCE_DIR}/test_case_all_senders.config ${CMAKE_CURRENT_BINARY_DIR}/test_case_all_senders.config COPYONLY)    
configure_file(${PROJECT_SOURCE_DIR}/test_case_all_receivers.config ${CMAKE_CURRENT_BINARY_DIR}/test_case_all_receivers.config COPYONLY)    
configure_file(${PROJECT_SOURCE_DIR}/developer_test.config ${CMAKE_CURRENT_BINARY_DIR}/developer_test.config COPYONLY)    
configure_file(${PROJECT_SOURCE_DIR}/durable_subscription.config ${CMAKE_CURRENT_BINARY_DIR}/durable_subscription.config COPYONLY)    

configure_file(${PROJECT_SOURCE_DIR}/test_message_file1.txt ${CMAKE_CURRENT_BINARY_DIR}/test_message_file1.txt COPYONLY)    
configure_file(${PROJECT_SOURCE_DIR}/test_message_file2.txt ${CMAKE_CURRENT_BINARY_DIR}/test_message_file2.txt COPYONLY)    
configure_file(${PROJECT_SOURCE_DIR}/test_message_file3.txt ${CMAKE_CURRENT_BINARY_DIR}/test_message_file3.txt COPYONLY)    
configure_file(${PROJECT_SOURCE_DIR}/test_message_file4.txt ${CMAKE_CURRENT_BINARY_DIR}/test_message_file4.txt COPYONLY)    

configure_file(${PROJECT_SOURCE_DIR}/logger.xml ${CMAKE_CURRENT_BINARY_DIR}/logger.xml COPYONLY)    

