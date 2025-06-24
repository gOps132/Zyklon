#
#   Made by Epilan Gian Cedrick G.
#
cmake_minimum_required(VERSION 3.14)

project(Zyklon 
		VERSION 1.0.0
		DESCRIPTION "Zyklon Game Engine Demo"
		LANGUAGES CXX)

# Ensure consistent runtime library settings
if(MSVC)
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
endif()

set(HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/header)
set(VENDOR_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/vendor)

add_subdirectory(lib/glfw)
add_subdirectory(lib/glad)
add_subdirectory(lib/glm)
add_subdirectory(lib/spdlog)
add_subdirectory(lib/ZyklonProfiler)
# NOTE: needs to be in docking branch
# add_subdirectory(lib/imgui-cmake)
add_subdirectory(lib/imgui-test)
add_subdirectory(lib/stb)
add_subdirectory(lib/voro)

include(cmake/StaticAnalyzers.cmake)
include(cmake/CompilerWarnings.cmake)

set(ENABLE_CLANG_TIDY           ON)
set(ENBALE_CPPCHECK             ON)
set(ENABLE_INCLUDE_WHAT_YOU_USE ON)

option(ZYKLON_ENABLE_OPENGL ON)
# if(APPLE)
#     set(PLATFORM_SOURCES 
#         src/Zyklon/Platform/Macos/MacosWindow.cpp
#         src/Zyklon/Platform/Macos/MacosInput.cpp
#     )
# elseif(WIN32)
#     set(PLATFORM_SOURCES
#         src/Zyklon/Platform/Windows/WindowsWindow.cpp
#         src/Zyklon/Platform/Windows/WindowsInput.cpp
#     )
# elseif(UNIX AND NOT APPLE)
#     set(PLATFORM_SOURCES 
#         src/Zyklon/Platform/Linux/LinuxWindow.cpp
#         src/Zyklon/Platform/Linux/LinuxInput.cpp
#     )
# endif()

set(ZYKLON_DIRECTORY 	"${CMAKE_CURRENT_SOURCE_DIR}/src/Zyklon")
set(CORE_DIRECTORY		"${ZYKLON_DIRECTORY}/Core")
set(IMGUI_DIRECTORY 	"${ZYKLON_DIRECTORY}/Imgui")
set(RENDERER_DIRECTORY 	"${ZYKLON_DIRECTORY}/Renderer")
set(COMPONENT_DIRECTORY "${ZYKLON_DIRECTORY}/Components")
set(PLATFORM_DIRECTORY 	"${ZYKLON_DIRECTORY}/Platform")


set(OPENGL_SOURCE_FILES
	${PLATFORM_DIRECTORY}/OpenGL/OpenGLContext.cpp
	${PLATFORM_DIRECTORY}/OpenGL/OpenGLShader.cpp
	${PLATFORM_DIRECTORY}/OpenGL/OpenGLBuffer.cpp
	${PLATFORM_DIRECTORY}/OpenGL/OpenGLVertexArray.cpp
	${PLATFORM_DIRECTORY}/OpenGL/OpenGLErrorManager.cpp
	${PLATFORM_DIRECTORY}/OpenGL/OpenGLRendererAPI.cpp
	${PLATFORM_DIRECTORY}/OpenGL/OpenGLTexture.cpp
)

set(PLATFORM_SOURCES 
	${PLATFORM_DIRECTORY}/Linux/LinuxWindow.cpp
	${PLATFORM_DIRECTORY}/Linux/LinuxInput.cpp
	${OPENGL_SOURCE_FILES}
)

set(RENDERER_SOURCE_FILES 
	${RENDERER_DIRECTORY}/GraphicsContext.cpp
	${RENDERER_DIRECTORY}/RendererAPI.cpp
	${RENDERER_DIRECTORY}/Renderer.cpp
	${RENDERER_DIRECTORY}/Buffer.cpp
	${RENDERER_DIRECTORY}/Shader.cpp
	${RENDERER_DIRECTORY}/VertexArray.cpp
	${RENDERER_DIRECTORY}/RenderCommand.cpp
	${RENDERER_DIRECTORY}/Texture.cpp
	${RENDERER_DIRECTORY}/Mesh.cpp
	${RENDERER_DIRECTORY}/Material.cpp

	${RENDERER_DIRECTORY}/Camera/OrthographicCamera.cpp
	${RENDERER_DIRECTORY}/Camera/PerspectiveCamera.cpp
	${RENDERER_DIRECTORY}/Camera/OrbitControls.cpp
)

set(IMGUI_SOURCE_FILES
	${IMGUI_DIRECTORY}/ImguiLayer.cpp
	${IMGUI_DIRECTORY}/ImguiBuild.cpp
)

set(ZYKLON_CORE_FILES
	${CORE_DIRECTORY}/Application.cpp
	${CORE_DIRECTORY}/Log.cpp
	${CORE_DIRECTORY}/Layer.cpp
	${CORE_DIRECTORY}/LayerStack.cpp
	${CORE_DIRECTORY}/UUID.cpp
	${CORE_DIRECTORY}/GameObject.cpp
	${CORE_DIRECTORY}/Scene.cpp
)

set(ZYKLON_COMPONENT_FILES
	${COMPONENT_DIRECTORY}/Component.cpp
)

set(ZYKLON_SOURCE_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/src/zyklon_pch.cpp
	${ZYKLON_CORE_FILES}
	${ZYKLON_COMPONENT_FILES}
	${IMGUI_SOURCE_FILES}
	${RENDERER_SOURCE_FILES}
	${PLATFORM_SOURCES}
)

set(CMAKE_CXX_VISIBILITY_PRESET         hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN     YES)

# ------------------------------------------
# BUILD TYPE FLAGS
# ------------------------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG
	"-Dzyklon_ENABLE_ASSERTS"
)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

# ------------------------------------------
# GENERATE ZYKLON STATIC LIBRARY
# ------------------------------------------
add_library(${PROJECT_NAME} STATIC ${ZYKLON_SOURCE_FILES})

# ------------------------------------------
# EXTERNAL
# ------------------------------------------
set(WARNINGS_AS_ERRORS OFF)
set_project_warnings(${PROJECT_NAME})

# ------------------------------------------
# GENERATING DLL VISIBILITY EXPORT HEADERS
# ------------------------------------------
include(GenerateExportHeader)
generate_export_header(${PROJECT_NAME} EXPORT_FILE_NAME ${ZYKLON_DIRECTORY}/zyklon_exports.h)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ------------------------------------------
# BUILD FLAGS
# ------------------------------------------
set_target_properties(${PROJECT_NAME} PROPERTIES 
	LINKER_LANGUAGE CXX

	SOVERSION	${PROJECT_VERSION_MAJOR}
	VERSION		${PROJECT_VERSION}

	LIBRARY_OUTPUT_DIRECTORY	"${CMAKE_SOURCE_DIR}/bin/${PROJECT_NAME}-${CMAKE_BUILD_TYPE}"
	ARCHIVE_OUTPUT_DIRECTORY	"${CMAKE_SOURCE_DIR}/bin/${PROJECT_NAME}-${CMAKE_BUILD_TYPE}"

	DEFINITIONS -Dzyklon_EXPORTS
)

# ------------------------------------------
# DEBUG FLAGS
# ------------------------------------------

# Not sure if MSVC supports the g flag
# set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

# ------------------------------------------
# PLATFORM SPECIFIC MACRO DEFINITIONS
# ------------------------------------------
if(APPLE)
	target_compile_definitions(${PROJECT_NAME} PRIVATE -DZYKLON_PLATFORM_MACOS)
elseif(WIN32)
	target_compile_definitions(${PROJECT_NAME} 
		PRIVATE		-DZYKLON_PLATFORM_WINDOWS
		PUBLIC		-DGLFW_INCLUDE_NONE
	)
elseif(UNIX AND NOT APPLE)
	target_compile_definitions(${PROJECT_NAME} PRIVATE -DZYKLON_PLATFORM_LINUX )
endif()

if(ZYKLON_ENABLE_OPENGL)
	target_compile_definitions(${PROJECT_NAME} PRIVATE -DZYKLON_ENABLE_OPENGL)
else()
	target_compile_definitions(${PROJECT_NAME} PRIVATE -DZYKLON_ENABLE_OPENGL)
endif()

if (APPLE)
	list (APPEND EXTRA_LIBS "-framework OpenGL")
elseif(WIN32)
	list (APPEND EXTRA_LIBS "-lgu32 -lopengl32")
	# set(CMAKE_EXE_LINKER_FLAGS "-std=gnu99 -static -static-libgcc -static-libstdc++ -mwindows")
	set(CMAKE_EXE_LINKER_FLAGS "-static-libstdc++ -mwindows")
elseif(UNIX AND NOT APPLE)
	list(APPEND EXTRA_LIBS "-lGL -lGLU -lX11")
endif()

set(IMGUI_EXAMPLES OFF)
set(IMGUI_IMPL_SDL OFF)
set(VORO_BUILD_SHARED_LIBS OFF)
target_link_libraries(
		${PROJECT_NAME}
		PRIVATE		${EXTRA_LIBS}
		PRIVATE		glfw
		PRIVATE		glad
		
		PUBLIC		zyklon_profiler_header_only
		PUBLIC		glm
		PUBLIC		imgui-test
		PUBLIC		spdlog
		PUBLIC		stb
		PUBLIC		voro++
)

target_precompile_headers(
	${PROJECT_NAME}
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/zyklon_pch.h
)

target_include_directories(${PROJECT_NAME}
	PUBLIC		${CMAKE_CURRENT_SOURCE_DIR}/vendor
	PUBLIC		${CMAKE_CURRENT_SOURCE_DIR}/src

	PRIVATE		${RENDERER_DIRECTORY}
	PRIVATE		${ZYKLON_DIRECTORY}
	PRIVATE		${IMGUI_DIRECTORY}
	PRIVATE		${PLATFORM_DIRECTORY}
)

# ------------------------------------------
# BUILD EXAMPLES
# ------------------------------------------
option(BUILD_ZYKLON_EXAMPLES "Build the sandbox project" OFF)
if(BUILD_ZYKLON_EXAMPLES)
	add_subdirectory(examples/Sandbox)
	add_subdirectory(examples/Grid)
	add_subdirectory(examples/Gravity)
	add_subdirectory(examples/Maze)
	add_subdirectory(examples/Plane)
endif()