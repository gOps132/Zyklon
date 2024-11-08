#
#   Made by Epilan Gian Cedrick G.
#
#   a project template for the game engine demo project
#

cmake_minimum_required(VERSION 3.14)
project(Gravity C CXX)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE
	src/Gravity.cpp
	src/Sphere.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE})

target_link_libraries(${PROJECT_NAME} Zyklon)

set_target_properties(${PROJECT_NAME} PROPERTIES 
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${PROJECT_NAME}-${CMAKE_BUILD_TYPE}"
)