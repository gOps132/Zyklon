# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.25.1/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.25.1/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/giancedrickepilan/dev/projects/Zyklon

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/giancedrickepilan/dev/projects/Zyklon/cmake

# Utility rule file for ExperimentalBuild.

# Include any custom commands dependencies for this target.
include lib/spdlog/CMakeFiles/ExperimentalBuild.dir/compiler_depend.make

# Include the progress variables for this target.
include lib/spdlog/CMakeFiles/ExperimentalBuild.dir/progress.make

lib/spdlog/CMakeFiles/ExperimentalBuild:
	cd /Users/giancedrickepilan/dev/projects/Zyklon/cmake/lib/spdlog && /usr/local/Cellar/cmake/3.25.1/bin/ctest -D ExperimentalBuild

ExperimentalBuild: lib/spdlog/CMakeFiles/ExperimentalBuild
ExperimentalBuild: lib/spdlog/CMakeFiles/ExperimentalBuild.dir/build.make
.PHONY : ExperimentalBuild

# Rule to build all files generated by this target.
lib/spdlog/CMakeFiles/ExperimentalBuild.dir/build: ExperimentalBuild
.PHONY : lib/spdlog/CMakeFiles/ExperimentalBuild.dir/build

lib/spdlog/CMakeFiles/ExperimentalBuild.dir/clean:
	cd /Users/giancedrickepilan/dev/projects/Zyklon/cmake/lib/spdlog && $(CMAKE_COMMAND) -P CMakeFiles/ExperimentalBuild.dir/cmake_clean.cmake
.PHONY : lib/spdlog/CMakeFiles/ExperimentalBuild.dir/clean

lib/spdlog/CMakeFiles/ExperimentalBuild.dir/depend:
	cd /Users/giancedrickepilan/dev/projects/Zyklon/cmake && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/giancedrickepilan/dev/projects/Zyklon /Users/giancedrickepilan/dev/projects/Zyklon/lib/spdlog /Users/giancedrickepilan/dev/projects/Zyklon/cmake /Users/giancedrickepilan/dev/projects/Zyklon/cmake/lib/spdlog /Users/giancedrickepilan/dev/projects/Zyklon/cmake/lib/spdlog/CMakeFiles/ExperimentalBuild.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/spdlog/CMakeFiles/ExperimentalBuild.dir/depend

