#
#   Made by Epilan Gian Cedrick G.
#
#   a project template for the game engine demo project
#

cmake_minimum_required(VERSION 3.14)
project(Sandbox C CXX)
set(TARGET_NAME sandbox)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE
   src/Sandbox.cpp
)

add_executable(${TARGET_NAME} ${SOURCE})

target_link_libraries(${TARGET_NAME} Zyklon)

set_target_properties(${TARGET_NAME} PROPERTIES 
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${PROJECT_NAME}-${CMAKE_BUILD_TYPE}"
)