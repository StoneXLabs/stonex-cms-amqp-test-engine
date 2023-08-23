cmake_minimum_required(VERSION 3.16)
project(send-receive-test LANGUAGES CXX DESCRIPTION "stonex cms client send receive tests")

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 20)



file(GLOB sourceFiles 
	${PROJECT_SOURCE_DIR}/*.cpp
	)
file(GLOB headerFiles 
	${PROJECT_SOURCE_DIR}/*.h	
	)


source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${sourceFiles} ${headerFiles})

add_executable(send-receive-test ${sourceFiles} ${headerFiles})              

target_include_directories(send-receive-test 
	PUBLIC ${PROJECT_SOURCE_DIR}/include
	)




if (UNIX)
	target_link_libraries(send-receive-test
		CONAN_PKG::stonex-cms-amqp-lib
		message-receiver
		message-sender
	)
else()
	target_link_libraries(send-receive-test
		message-receiver
		message-sender
		secur32 
		crypt32 
		Ws2_32
	)
endif()

