# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.27

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\foste\Downloads\assignment

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\foste\Downloads\assignment\build

# Include any dependencies generated for this target.
include CMakeFiles/interactive.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/interactive.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/interactive.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/interactive.dir/flags.make

CMakeFiles/interactive.dir/interface.c.obj: CMakeFiles/interactive.dir/flags.make
CMakeFiles/interactive.dir/interface.c.obj: CMakeFiles/interactive.dir/includes_C.rsp
CMakeFiles/interactive.dir/interface.c.obj: C:/Users/foste/Downloads/assignment/interface.c
CMakeFiles/interactive.dir/interface.c.obj: CMakeFiles/interactive.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\foste\Downloads\assignment\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/interactive.dir/interface.c.obj"
	C:\Users\foste\Downloads\mingw64-13.1.0\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/interactive.dir/interface.c.obj -MF CMakeFiles\interactive.dir\interface.c.obj.d -o CMakeFiles\interactive.dir\interface.c.obj -c C:\Users\foste\Downloads\assignment\interface.c

CMakeFiles/interactive.dir/interface.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/interactive.dir/interface.c.i"
	C:\Users\foste\Downloads\mingw64-13.1.0\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\foste\Downloads\assignment\interface.c > CMakeFiles\interactive.dir\interface.c.i

CMakeFiles/interactive.dir/interface.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/interactive.dir/interface.c.s"
	C:\Users\foste\Downloads\mingw64-13.1.0\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\foste\Downloads\assignment\interface.c -o CMakeFiles\interactive.dir\interface.c.s

# Object files for target interactive
interactive_OBJECTS = \
"CMakeFiles/interactive.dir/interface.c.obj"

# External object files for target interactive
interactive_EXTERNAL_OBJECTS = \
"C:/Users/foste/Downloads/assignment/build/CMakeFiles/model.dir/model.c.obj"

interactive.exe: CMakeFiles/interactive.dir/interface.c.obj
interactive.exe: CMakeFiles/model.dir/model.c.obj
interactive.exe: CMakeFiles/interactive.dir/build.make
interactive.exe: CMakeFiles/interactive.dir/linkLibs.rsp
interactive.exe: CMakeFiles/interactive.dir/objects1.rsp
interactive.exe: CMakeFiles/interactive.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\foste\Downloads\assignment\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable interactive.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\interactive.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/interactive.dir/build: interactive.exe
.PHONY : CMakeFiles/interactive.dir/build

CMakeFiles/interactive.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\interactive.dir\cmake_clean.cmake
.PHONY : CMakeFiles/interactive.dir/clean

CMakeFiles/interactive.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\foste\Downloads\assignment C:\Users\foste\Downloads\assignment C:\Users\foste\Downloads\assignment\build C:\Users\foste\Downloads\assignment\build C:\Users\foste\Downloads\assignment\build\CMakeFiles\interactive.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/interactive.dir/depend

