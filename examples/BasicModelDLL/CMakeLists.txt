#
#   DLL Example - Demonstrates Zyklon as shared library
#

cmake_minimum_required(VERSION 3.14)
project(BasicModelDLL C CXX)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE
	src/BasicModelDLL.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE})

set(ZYKLON_BUILD_SHARED ON)
target_link_libraries(${PROJECT_NAME} 
	Zyklon
)

# Copy DLL to executable directory on Windows
if(WIN32 AND ZYKLON_BUILD_SHARED)
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
		$<TARGET_FILE:Zyklon>
		$<TARGET_FILE_DIR:${PROJECT_NAME}>)
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES 
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${PROJECT_NAME}-${CMAKE_BUILD_TYPE}"
)