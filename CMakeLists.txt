#
#   Made by Epilan Gian Cedrick G.
#
cmake_minimum_required(VERSION 3.14)

project(Zyklon 
        VERSION 1.0.0
        DESCRIPTION "Zyklon Game Engine Demo"
        LANGUAGES CXX)

set(HEADER_DIR "src/header")
set(VENDOR_DIR "src/vendor")

add_subdirectory(lib/glfw)
add_subdirectory(lib/glad)
add_subdirectory(lib/glm)
add_subdirectory(lib/spdlog)
add_subdirectory(lib/ZyklonProfiler)
# NOTE: needs to be in docking branch
# add_subdirectory(lib/imgui-cmake)
add_subdirectory(lib/imgui-test)

include(cmake/StaticAnalyzers.cmake)
include(cmake/CompilerWarnings.cmake)

set(ENABLE_CLANG_TIDY           ON)
set(ENBALE_CPPCHECK             ON)
set(ENABLE_INCLUDE_WHAT_YOU_USE ON)

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

set(PLATFORM_SOURCES 
    src/Zyklon/Platform/Linux/LinuxWindow.cpp
    src/Zyklon/Platform/Linux/LinuxInput.cpp
)

# TODO: add abstraction test for build time and runtime
set(RENDER_API_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/Renderer/API")
set(GRAPHICS_API 
    src/Renderer/Renderer.cpp
    src/Renderer/Buffer.cpp
    src/Renderer/Shader.cpp
    src/Renderer/VertexArray.cpp

    ${RENDER_API_DIR}/OpenGL/OpenGLContext.cpp
    ${RENDER_API_DIR}/OpenGL/OpenGLShader.cpp
    ${RENDER_API_DIR}/OpenGL/OpenGLBuffer.cpp
    ${RENDER_API_DIR}/OpenGL/OpenGLVertexArray.cpp
    ${RENDER_API_DIR}/OpenGL/OpenGLErrorManager.cpp
)

set(ZYKLON_SOURCE_FILES
    src/Zyklon/Application.cpp
    src/Zyklon/Log.cpp
    src/Zyklon/Layer.cpp
    src/Zyklon/LayerStack.cpp
    src/Zyklon/zyklon_pch.cpp

    src/Imgui/ImguiLayer.cpp
    src/Imgui/ImguiBuild.cpp

    ${GRAPHICS_API}
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
generate_export_header(${PROJECT_NAME} EXPORT_FILE_NAME ${CMAKE_CURRENT_SOURCE_DIR}/src/Zyklon/zyklon_exports.h)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ------------------------------------------
# BUILD FLAGS
# ------------------------------------------
set_target_properties(${PROJECT_NAME} PROPERTIES 
    LINKER_LANGUAGE CXX

    SOVERSION   ${PROJECT_VERSION_MAJOR}
    VERSION     ${PROJECT_VERSION}

    LIBRARY_OUTPUT_DIRECTORY        "${CMAKE_SOURCE_DIR}/bin/${PROJECT_NAME}-${CMAKE_BUILD_TYPE}"
    ARCHIVE_OUTPUT_DIRECTORY        "${CMAKE_SOURCE_DIR}/bin/${PROJECT_NAME}-${CMAKE_BUILD_TYPE}"

    DEFINITIONS -Dzyklon_EXPORTS
)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
    option(RUNTIME_STATIC_LINKAGE "Link with runtime library statically" OFF)
endif(MSVC) 

# If the runtime static linkage option is turned on, replace
# compiler flag that selects runtime library variant.
if(MSVC AND RUNTIME_STATIC_LINKAGE)
    foreach(flag
        CMAKE_C_FLAGS
        CMAKE_CXX_FLAGS
        CMAKE_C_FLAGS_DEBUG
        CMAKE_CXX_FLAGS_DEBUG
        CMAKE_C_FLAGS_RELEASE
        CMAKE_CXX_FLAGS_RELEASE
        CMAKE_C_FLAGS_MINSIZEREL
        CMAKE_CXX_FLAGS_MINSIZEREL
        CMAKE_C_FLAGS_RELWITHDEBINFO
        CMAKE_CXX_FLAGS_RELWITHDEBINFO
    )
        if(${flag} MATCHES "/MD")
            string(REGEX REPLACE "/MD" "/MT" ${flag} "${${flag}}")
        endif(${flag} MATCHES "/MD")
    endforeach(flag)
endif(MSVC AND RUNTIME_STATIC_LINKAGE)

# ------------------------------------------
# DEBUG FLAGS
# ------------------------------------------

# Not sure if MSVC supports the g flag
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

# if(MSVC)
#   # using Visual Studio C++
# elseif(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
#     set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -pg")
# elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
#     set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
# else()
#     message(AUTHOR_WARNING "No compiler debug set for '${CMAKE_CXX_COMPILER_ID}' compiler.")
# endif()

# ------------------------------------------
# PLATFORM SPECIFIC MACRO DEFINITIONS
# ------------------------------------------
if(APPLE)
    target_compile_definitions(${PROJECT_NAME} 
        PRIVATE     -DZYKLON_PLATFORM_MACOS
    )
elseif(WIN32)
    target_compile_definitions(${PROJECT_NAME} 
        PRIVATE     -DZYKLON_PLATFORM_WINDOWS
        PUBLIC      -DGLFW_INCLUDE_NONE
    )
elseif(UNIX AND NOT APPLE)
    target_compile_definitions(${PROJECT_NAME} 
        PRIVATE     -DZYKLON_PLATFORM_LINUX
    )
endif()

if (APPLE)
    list (APPEND EXTRA_LIBS "-framework OpenGL")
elseif(WIN32)
    list (APPEND EXTRA_LIBS "-lgu32 -lopengl32")
    set(CMAKE_EXE_LINKER_FLAGS "-std=gnu99 -static -static-libgcc -static-libstdc++ -mwindows")
elseif(UNIX AND NOT APPLE)
    list(APPEND EXTRA_LIBS "-lGL -lGLU -lX11")
endif()

set(IMGUI_EXAMPLES OFF)
set(IMGUI_IMPL_SDL OFF)
target_link_libraries(
        ${PROJECT_NAME}
        PRIVATE     ${EXTRA_LIBS}
        PUBLIC      zyklon_profiler_header_only
        PRIVATE     glfw
        PRIVATE     glad
        PUBLIC      glm
        PUBLIC      imgui-test
        PUBLIC      spdlog
)

target_precompile_headers(
    ${PROJECT_NAME}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/Zyklon/zyklon_pch.h
)

target_include_directories(${PROJECT_NAME}
    PUBLIC      ${CMAKE_CURRENT_SOURCE_DIR}/src
    PUBLIC      ${CMAKE_CURRENT_SOURCE_DIR}/vendor
)

# ------------------------------------------
# BUILD EXAMPLES
# ------------------------------------------
option(BUILD_ZYKLON_EXAMPLES "Build the sandbox project" OFF)
if(BUILD_ZYKLON_EXAMPLES)
    add_subdirectory(examples/Sandbox)
endif()