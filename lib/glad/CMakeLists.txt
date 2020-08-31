cmake_minimum_required(VERSION 3.14)
project(glad
	DESCRIPTION "Simple cmake glad wrapper"
)

add_library(${PROJECT_NAME} STATIC
	src/glad.c
)

# FIX COMPILE ERROR (still don't know what this compile flag means)
set_target_properties(${PROJECT_NAME} PROPERTIES 
	COMPILE_FLAGS -fPIC
)

target_include_directories(
	${PROJECT_NAME}
	PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)