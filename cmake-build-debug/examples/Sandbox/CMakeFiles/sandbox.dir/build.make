# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/giancedrickepilan/dev/engine/Zyklon

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/giancedrickepilan/dev/engine/Zyklon/cmake-build-debug

# Include any dependencies generated for this target.
include examples/Sandbox/CMakeFiles/sandbox.dir/depend.make

# Include the progress variables for this target.
include examples/Sandbox/CMakeFiles/sandbox.dir/progress.make

# Include the compile flags for this target's objects.
include examples/Sandbox/CMakeFiles/sandbox.dir/flags.make

examples/Sandbox/CMakeFiles/sandbox.dir/src/Sandbox.cpp.o: examples/Sandbox/CMakeFiles/sandbox.dir/flags.make
examples/Sandbox/CMakeFiles/sandbox.dir/src/Sandbox.cpp.o: ../examples/Sandbox/src/Sandbox.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/giancedrickepilan/dev/engine/Zyklon/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object examples/Sandbox/CMakeFiles/sandbox.dir/src/Sandbox.cpp.o"
	cd /Users/giancedrickepilan/dev/engine/Zyklon/cmake-build-debug/examples/Sandbox && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/sandbox.dir/src/Sandbox.cpp.o -c /Users/giancedrickepilan/dev/engine/Zyklon/examples/Sandbox/src/Sandbox.cpp

examples/Sandbox/CMakeFiles/sandbox.dir/src/Sandbox.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/sandbox.dir/src/Sandbox.cpp.i"
	cd /Users/giancedrickepilan/dev/engine/Zyklon/cmake-build-debug/examples/Sandbox && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/giancedrickepilan/dev/engine/Zyklon/examples/Sandbox/src/Sandbox.cpp > CMakeFiles/sandbox.dir/src/Sandbox.cpp.i

examples/Sandbox/CMakeFiles/sandbox.dir/src/Sandbox.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/sandbox.dir/src/Sandbox.cpp.s"
	cd /Users/giancedrickepilan/dev/engine/Zyklon/cmake-build-debug/examples/Sandbox && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/giancedrickepilan/dev/engine/Zyklon/examples/Sandbox/src/Sandbox.cpp -o CMakeFiles/sandbox.dir/src/Sandbox.cpp.s

# Object files for target sandbox
sandbox_OBJECTS = \
"CMakeFiles/sandbox.dir/src/Sandbox.cpp.o"

# External object files for target sandbox
sandbox_EXTERNAL_OBJECTS =

../bin/Sandbox-Debug/sandbox: examples/Sandbox/CMakeFiles/sandbox.dir/src/Sandbox.cpp.o
../bin/Sandbox-Debug/sandbox: examples/Sandbox/CMakeFiles/sandbox.dir/build.make
../bin/Sandbox-Debug/sandbox: ../bin/Zyklon-Debug/libZyklon.a
../bin/Sandbox-Debug/sandbox: lib/glfw/src/libglfw3.a
../bin/Sandbox-Debug/sandbox: lib/glad/libglad.a
../bin/Sandbox-Debug/sandbox: lib/imgui-test/libimgui-test.a
../bin/Sandbox-Debug/sandbox: examples/Sandbox/CMakeFiles/sandbox.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/giancedrickepilan/dev/engine/Zyklon/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../../bin/Sandbox-Debug/sandbox"
	cd /Users/giancedrickepilan/dev/engine/Zyklon/cmake-build-debug/examples/Sandbox && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sandbox.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/Sandbox/CMakeFiles/sandbox.dir/build: ../bin/Sandbox-Debug/sandbox

.PHONY : examples/Sandbox/CMakeFiles/sandbox.dir/build

examples/Sandbox/CMakeFiles/sandbox.dir/clean:
	cd /Users/giancedrickepilan/dev/engine/Zyklon/cmake-build-debug/examples/Sandbox && $(CMAKE_COMMAND) -P CMakeFiles/sandbox.dir/cmake_clean.cmake
.PHONY : examples/Sandbox/CMakeFiles/sandbox.dir/clean

examples/Sandbox/CMakeFiles/sandbox.dir/depend:
	cd /Users/giancedrickepilan/dev/engine/Zyklon/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/giancedrickepilan/dev/engine/Zyklon /Users/giancedrickepilan/dev/engine/Zyklon/examples/Sandbox /Users/giancedrickepilan/dev/engine/Zyklon/cmake-build-debug /Users/giancedrickepilan/dev/engine/Zyklon/cmake-build-debug/examples/Sandbox /Users/giancedrickepilan/dev/engine/Zyklon/cmake-build-debug/examples/Sandbox/CMakeFiles/sandbox.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/Sandbox/CMakeFiles/sandbox.dir/depend

