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
include lib/imgui-test/CMakeFiles/imgui-test.dir/depend.make

# Include the progress variables for this target.
include lib/imgui-test/CMakeFiles/imgui-test.dir/progress.make

# Include the compile flags for this target's objects.
include lib/imgui-test/CMakeFiles/imgui-test.dir/flags.make

lib/imgui-test/CMakeFiles/imgui-test.dir/imgui.cpp.o: lib/imgui-test/CMakeFiles/imgui-test.dir/flags.make
lib/imgui-test/CMakeFiles/imgui-test.dir/imgui.cpp.o: ../lib/imgui-test/imgui.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/giancedrickepilan/dev/engine/Zyklon/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object lib/imgui-test/CMakeFiles/imgui-test.dir/imgui.cpp.o"
	cd /Users/giancedrickepilan/dev/engine/Zyklon/cmake-build-debug/lib/imgui-test && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/imgui-test.dir/imgui.cpp.o -c /Users/giancedrickepilan/dev/engine/Zyklon/lib/imgui-test/imgui.cpp

lib/imgui-test/CMakeFiles/imgui-test.dir/imgui.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imgui-test.dir/imgui.cpp.i"
	cd /Users/giancedrickepilan/dev/engine/Zyklon/cmake-build-debug/lib/imgui-test && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/giancedrickepilan/dev/engine/Zyklon/lib/imgui-test/imgui.cpp > CMakeFiles/imgui-test.dir/imgui.cpp.i

lib/imgui-test/CMakeFiles/imgui-test.dir/imgui.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imgui-test.dir/imgui.cpp.s"
	cd /Users/giancedrickepilan/dev/engine/Zyklon/cmake-build-debug/lib/imgui-test && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/giancedrickepilan/dev/engine/Zyklon/lib/imgui-test/imgui.cpp -o CMakeFiles/imgui-test.dir/imgui.cpp.s

lib/imgui-test/CMakeFiles/imgui-test.dir/imgui_draw.cpp.o: lib/imgui-test/CMakeFiles/imgui-test.dir/flags.make
lib/imgui-test/CMakeFiles/imgui-test.dir/imgui_draw.cpp.o: ../lib/imgui-test/imgui_draw.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/giancedrickepilan/dev/engine/Zyklon/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object lib/imgui-test/CMakeFiles/imgui-test.dir/imgui_draw.cpp.o"
	cd /Users/giancedrickepilan/dev/engine/Zyklon/cmake-build-debug/lib/imgui-test && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/imgui-test.dir/imgui_draw.cpp.o -c /Users/giancedrickepilan/dev/engine/Zyklon/lib/imgui-test/imgui_draw.cpp

lib/imgui-test/CMakeFiles/imgui-test.dir/imgui_draw.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imgui-test.dir/imgui_draw.cpp.i"
	cd /Users/giancedrickepilan/dev/engine/Zyklon/cmake-build-debug/lib/imgui-test && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/giancedrickepilan/dev/engine/Zyklon/lib/imgui-test/imgui_draw.cpp > CMakeFiles/imgui-test.dir/imgui_draw.cpp.i

lib/imgui-test/CMakeFiles/imgui-test.dir/imgui_draw.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imgui-test.dir/imgui_draw.cpp.s"
	cd /Users/giancedrickepilan/dev/engine/Zyklon/cmake-build-debug/lib/imgui-test && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/giancedrickepilan/dev/engine/Zyklon/lib/imgui-test/imgui_draw.cpp -o CMakeFiles/imgui-test.dir/imgui_draw.cpp.s

lib/imgui-test/CMakeFiles/imgui-test.dir/imgui_widgets.cpp.o: lib/imgui-test/CMakeFiles/imgui-test.dir/flags.make
lib/imgui-test/CMakeFiles/imgui-test.dir/imgui_widgets.cpp.o: ../lib/imgui-test/imgui_widgets.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/giancedrickepilan/dev/engine/Zyklon/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object lib/imgui-test/CMakeFiles/imgui-test.dir/imgui_widgets.cpp.o"
	cd /Users/giancedrickepilan/dev/engine/Zyklon/cmake-build-debug/lib/imgui-test && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/imgui-test.dir/imgui_widgets.cpp.o -c /Users/giancedrickepilan/dev/engine/Zyklon/lib/imgui-test/imgui_widgets.cpp

lib/imgui-test/CMakeFiles/imgui-test.dir/imgui_widgets.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imgui-test.dir/imgui_widgets.cpp.i"
	cd /Users/giancedrickepilan/dev/engine/Zyklon/cmake-build-debug/lib/imgui-test && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/giancedrickepilan/dev/engine/Zyklon/lib/imgui-test/imgui_widgets.cpp > CMakeFiles/imgui-test.dir/imgui_widgets.cpp.i

lib/imgui-test/CMakeFiles/imgui-test.dir/imgui_widgets.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imgui-test.dir/imgui_widgets.cpp.s"
	cd /Users/giancedrickepilan/dev/engine/Zyklon/cmake-build-debug/lib/imgui-test && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/giancedrickepilan/dev/engine/Zyklon/lib/imgui-test/imgui_widgets.cpp -o CMakeFiles/imgui-test.dir/imgui_widgets.cpp.s

lib/imgui-test/CMakeFiles/imgui-test.dir/imgui_demo.cpp.o: lib/imgui-test/CMakeFiles/imgui-test.dir/flags.make
lib/imgui-test/CMakeFiles/imgui-test.dir/imgui_demo.cpp.o: ../lib/imgui-test/imgui_demo.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/giancedrickepilan/dev/engine/Zyklon/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object lib/imgui-test/CMakeFiles/imgui-test.dir/imgui_demo.cpp.o"
	cd /Users/giancedrickepilan/dev/engine/Zyklon/cmake-build-debug/lib/imgui-test && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/imgui-test.dir/imgui_demo.cpp.o -c /Users/giancedrickepilan/dev/engine/Zyklon/lib/imgui-test/imgui_demo.cpp

lib/imgui-test/CMakeFiles/imgui-test.dir/imgui_demo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/imgui-test.dir/imgui_demo.cpp.i"
	cd /Users/giancedrickepilan/dev/engine/Zyklon/cmake-build-debug/lib/imgui-test && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/giancedrickepilan/dev/engine/Zyklon/lib/imgui-test/imgui_demo.cpp > CMakeFiles/imgui-test.dir/imgui_demo.cpp.i

lib/imgui-test/CMakeFiles/imgui-test.dir/imgui_demo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/imgui-test.dir/imgui_demo.cpp.s"
	cd /Users/giancedrickepilan/dev/engine/Zyklon/cmake-build-debug/lib/imgui-test && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/giancedrickepilan/dev/engine/Zyklon/lib/imgui-test/imgui_demo.cpp -o CMakeFiles/imgui-test.dir/imgui_demo.cpp.s

# Object files for target imgui-test
imgui__test_OBJECTS = \
"CMakeFiles/imgui-test.dir/imgui.cpp.o" \
"CMakeFiles/imgui-test.dir/imgui_draw.cpp.o" \
"CMakeFiles/imgui-test.dir/imgui_widgets.cpp.o" \
"CMakeFiles/imgui-test.dir/imgui_demo.cpp.o"

# External object files for target imgui-test
imgui__test_EXTERNAL_OBJECTS =

lib/imgui-test/libimgui-test.a: lib/imgui-test/CMakeFiles/imgui-test.dir/imgui.cpp.o
lib/imgui-test/libimgui-test.a: lib/imgui-test/CMakeFiles/imgui-test.dir/imgui_draw.cpp.o
lib/imgui-test/libimgui-test.a: lib/imgui-test/CMakeFiles/imgui-test.dir/imgui_widgets.cpp.o
lib/imgui-test/libimgui-test.a: lib/imgui-test/CMakeFiles/imgui-test.dir/imgui_demo.cpp.o
lib/imgui-test/libimgui-test.a: lib/imgui-test/CMakeFiles/imgui-test.dir/build.make
lib/imgui-test/libimgui-test.a: lib/imgui-test/CMakeFiles/imgui-test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/giancedrickepilan/dev/engine/Zyklon/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX static library libimgui-test.a"
	cd /Users/giancedrickepilan/dev/engine/Zyklon/cmake-build-debug/lib/imgui-test && $(CMAKE_COMMAND) -P CMakeFiles/imgui-test.dir/cmake_clean_target.cmake
	cd /Users/giancedrickepilan/dev/engine/Zyklon/cmake-build-debug/lib/imgui-test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/imgui-test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lib/imgui-test/CMakeFiles/imgui-test.dir/build: lib/imgui-test/libimgui-test.a

.PHONY : lib/imgui-test/CMakeFiles/imgui-test.dir/build

lib/imgui-test/CMakeFiles/imgui-test.dir/clean:
	cd /Users/giancedrickepilan/dev/engine/Zyklon/cmake-build-debug/lib/imgui-test && $(CMAKE_COMMAND) -P CMakeFiles/imgui-test.dir/cmake_clean.cmake
.PHONY : lib/imgui-test/CMakeFiles/imgui-test.dir/clean

lib/imgui-test/CMakeFiles/imgui-test.dir/depend:
	cd /Users/giancedrickepilan/dev/engine/Zyklon/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/giancedrickepilan/dev/engine/Zyklon /Users/giancedrickepilan/dev/engine/Zyklon/lib/imgui-test /Users/giancedrickepilan/dev/engine/Zyklon/cmake-build-debug /Users/giancedrickepilan/dev/engine/Zyklon/cmake-build-debug/lib/imgui-test /Users/giancedrickepilan/dev/engine/Zyklon/cmake-build-debug/lib/imgui-test/CMakeFiles/imgui-test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lib/imgui-test/CMakeFiles/imgui-test.dir/depend

