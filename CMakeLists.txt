#
#   Made by Epilan Gian Cedrick G.
#

cmake_minimum_required(VERSION 3.14)

project(Zyklon 
        VERSION 1.0.0
        DESCRIPTION "Zyklon Game Engine Demo"
        LANGUAGES C CXX)

set(HEADER_DIR "src/header")
set(VENDOR_DIR "src/vendor")

add_subdirectory(lib/glfw)
add_subdirectory(lib/glad)
add_subdirectory(lib/glm)
add_subdirectory(lib/spdlog)

# NOTE: needs to be in docking branch
# add_subdirectory(lib/imgui-cmake)
add_subdirectory(lib/imgui-test)

if(APPLE)
    set(PLATFORM_SOURCES 
        src/Zyklon/Platform/Macos/MacosWindow.cpp
        src/Zyklon/Platform/Macos/MacosInput.cpp
    )
elseif(WIN32)
    set(PLATFORM_SOURCES
        src/Zyklon/Platform/Windows/WindowsWindow.cpp
        src/Zyklon/Platform/Windows/WindowsInput.cpp
    )
elseif(UNIX AND NOT APPLE)
    set(PLATFORM_SOURCES 
        src/Zyklon/Platform/Linux/LinuxWindow.cpp
        src/Zyklon/Platform/Linux/LinuxInput.cpp
    )
endif()

set(ZYKLON_SOURCE_FILES
    src/Zyklon/Application.cpp
    src/Zyklon/Log.cpp
    src/Zyklon/Layer.cpp
    src/Zyklon/LayerStack.cpp

    src/Imgui/ImguiLayer.cpp

    src/Imgui/ImguiBuild.cpp

    src/Zyklon/zyklon_pch.cpp

    ${PLATFORM_SOURCES}
)

# this may or may not cause some future problems
if(NOT APPLE)
    set(CMAKE_INSTALL_RPATH $ORIGIN)
endif()

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

add_library(${PROJECT_NAME} STATIC ${ZYKLON_SOURCE_FILES})

# ------------------------------------------
# GENERATING DLL VISIBILITY EXPORT HEADERS
# ------------------------------------------
include(GenerateExportHeader)
generate_export_header(${PROJECT_NAME} EXPORT_FILE_NAME ${CMAKE_CURRENT_SOURCE_DIR}/src/Zyklon/zyklon_exports.h)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ------------------------------------------
# OUTPUT BIN DIRECTORY DEFAULT
# ------------------------------------------
option(ZYKLON_OUTPUT_ENABLE "set ZYKLON_OUTPUT_BIN_DIR to specified output directory" OFF)
if(${ZYKLON_OUTPUT_ENABLE})
    message("you have overriden ZYKLON_OUTPUT_BIN_DIR")
else()
    set(ZYKLON_OUTPUT_BIN_DIR "${CMAKE_SOURCE_DIR}/bin")
endif()

# ------------------------------------------
# BUILD TYPE FLAGS
# ------------------------------------------
set_target_properties(${PROJECT_NAME} PROPERTIES 
    LINKER_LANGUAGE CXX

    SOVERSION   ${PROJECT_VERSION_MAJOR}
    VERSION     ${PROJECT_VERSION}

    LIBRARY_OUTPUT_DIRECTORY        "${ZYKLON_OUTPUT_BIN_DIR}/${PROJECT_NAME}-${CMAKE_BUILD_TYPE}"
    ARCHIVE_OUTPUT_DIRECTORY    "${ZYKLON_OUTPUT_BIN_DIR}/${PROJECT_NAME}-${CMAKE_BUILD_TYPE}"

    DEFINITIONS -Dzyklon_EXPORTS 
)

if(MSVC)
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
        PUBLIC      -lstdc++
        PRIVATE     glfw
        PRIVATE     glad
        PUBLIC      glm
        PUBLIC      imgui-test
        PUBLIC      spdlog_header_only
)

target_precompile_headers(
    ${PROJECT_NAME}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/Zyklon/zyklon_pch.h
)

target_include_directories(${PROJECT_NAME}
    PUBLIC      ${CMAKE_CURRENT_SOURCE_DIR}/src
    PUBLIC      ${CMAKE_CURRENT_SOURCE_DIR}/vendor
)