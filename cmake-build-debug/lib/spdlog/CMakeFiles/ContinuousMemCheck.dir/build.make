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

# Utility rule file for ContinuousMemCheck.

# Include the progress variables for this target.
include lib/spdlog/CMakeFiles/ContinuousMemCheck.dir/progress.make

lib/spdlog/CMakeFiles/ContinuousMemCheck:
	cd /Users/giancedrickepilan/dev/engine/Zyklon/cmake-build-debug/lib/spdlog && /Applications/CLion.app/Contents/bin/cmake/mac/bin/ctest -D ContinuousMemCheck

ContinuousMemCheck: lib/spdlog/CMakeFiles/ContinuousMemCheck
ContinuousMemCheck: lib/spdlog/CMakeFiles/ContinuousMemCheck.dir/build.make

.PHONY : ContinuousMemCheck

# Rule to build all files generated by this target.
lib/spdlog/CMakeFiles/ContinuousMemCheck.dir/build: ContinuousMemCheck

.PHONY : lib/spdlog/CMakeFiles/ContinuousMemCheck.dir/build

lib/spdlog/CMakeFiles/ContinuousMemCheck.dir/clean:
	cd /Users/giancedrickepilan/dev/engine/Zyklon/cmake-build-debug/lib/spdlog && $(CMAKE_COMMAND) -P CMakeFiles/ContinuousMemCheck.dir/cmake_clean.cmake
.PHONY : lib/spdlog/CMakeFiles/ContinuousMemCheck.dir/clean

lib/spdlog/CMakeFiles/ContinuousMemCheck.dir/depend:
	cd /Users/giancedrickepilan/dev/engine/Zyklon/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/giancedrickepilan/dev/engine/Zyklon /Users/giancedrickepilan/dev/engine/Zyklon/lib/spdlog /Users/giancedrickepilan/dev/engine/Zyklon/cmake-build-debug /Users/giancedrickepilan/dev/engine/Zyklon/cmake-build-debug/lib/spdlog /Users/giancedrickepilan/dev/engine/Zyklon/cmake-build-debug/lib/spdlog/CMakeFiles/ContinuousMemCheck.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/spdlog/CMakeFiles/ContinuousMemCheck.dir/depend

