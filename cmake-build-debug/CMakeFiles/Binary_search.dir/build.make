# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.9

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2017.3\bin\cmake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2017.3\bin\cmake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\John\Dropbox\MTM HW files\C HW 3\K's files\MTMex3"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\John\Dropbox\MTM HW files\C HW 3\K's files\MTMex3\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/Binary_search.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Binary_search.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Binary_search.dir/flags.make

CMakeFiles/Binary_search.dir/binary_search.c.obj: CMakeFiles/Binary_search.dir/flags.make
CMakeFiles/Binary_search.dir/binary_search.c.obj: ../binary_search.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\John\Dropbox\MTM HW files\C HW 3\K's files\MTMex3\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Binary_search.dir/binary_search.c.obj"
	D:\TDM-GCC-64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\Binary_search.dir\binary_search.c.obj   -c "C:\Users\John\Dropbox\MTM HW files\C HW 3\K's files\MTMex3\binary_search.c"

CMakeFiles/Binary_search.dir/binary_search.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Binary_search.dir/binary_search.c.i"
	D:\TDM-GCC-64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\Users\John\Dropbox\MTM HW files\C HW 3\K's files\MTMex3\binary_search.c" > CMakeFiles\Binary_search.dir\binary_search.c.i

CMakeFiles/Binary_search.dir/binary_search.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Binary_search.dir/binary_search.c.s"
	D:\TDM-GCC-64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:\Users\John\Dropbox\MTM HW files\C HW 3\K's files\MTMex3\binary_search.c" -o CMakeFiles\Binary_search.dir\binary_search.c.s

CMakeFiles/Binary_search.dir/binary_search.c.obj.requires:

.PHONY : CMakeFiles/Binary_search.dir/binary_search.c.obj.requires

CMakeFiles/Binary_search.dir/binary_search.c.obj.provides: CMakeFiles/Binary_search.dir/binary_search.c.obj.requires
	$(MAKE) -f CMakeFiles\Binary_search.dir\build.make CMakeFiles/Binary_search.dir/binary_search.c.obj.provides.build
.PHONY : CMakeFiles/Binary_search.dir/binary_search.c.obj.provides

CMakeFiles/Binary_search.dir/binary_search.c.obj.provides.build: CMakeFiles/Binary_search.dir/binary_search.c.obj


CMakeFiles/Binary_search.dir/connectedList.c.obj: CMakeFiles/Binary_search.dir/flags.make
CMakeFiles/Binary_search.dir/connectedList.c.obj: ../connectedList.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\John\Dropbox\MTM HW files\C HW 3\K's files\MTMex3\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/Binary_search.dir/connectedList.c.obj"
	D:\TDM-GCC-64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\Binary_search.dir\connectedList.c.obj   -c "C:\Users\John\Dropbox\MTM HW files\C HW 3\K's files\MTMex3\connectedList.c"

CMakeFiles/Binary_search.dir/connectedList.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Binary_search.dir/connectedList.c.i"
	D:\TDM-GCC-64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\Users\John\Dropbox\MTM HW files\C HW 3\K's files\MTMex3\connectedList.c" > CMakeFiles\Binary_search.dir\connectedList.c.i

CMakeFiles/Binary_search.dir/connectedList.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Binary_search.dir/connectedList.c.s"
	D:\TDM-GCC-64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:\Users\John\Dropbox\MTM HW files\C HW 3\K's files\MTMex3\connectedList.c" -o CMakeFiles\Binary_search.dir\connectedList.c.s

CMakeFiles/Binary_search.dir/connectedList.c.obj.requires:

.PHONY : CMakeFiles/Binary_search.dir/connectedList.c.obj.requires

CMakeFiles/Binary_search.dir/connectedList.c.obj.provides: CMakeFiles/Binary_search.dir/connectedList.c.obj.requires
	$(MAKE) -f CMakeFiles\Binary_search.dir\build.make CMakeFiles/Binary_search.dir/connectedList.c.obj.provides.build
.PHONY : CMakeFiles/Binary_search.dir/connectedList.c.obj.provides

CMakeFiles/Binary_search.dir/connectedList.c.obj.provides.build: CMakeFiles/Binary_search.dir/connectedList.c.obj


# Object files for target Binary_search
Binary_search_OBJECTS = \
"CMakeFiles/Binary_search.dir/binary_search.c.obj" \
"CMakeFiles/Binary_search.dir/connectedList.c.obj"

# External object files for target Binary_search
Binary_search_EXTERNAL_OBJECTS =

Binary_search.exe: CMakeFiles/Binary_search.dir/binary_search.c.obj
Binary_search.exe: CMakeFiles/Binary_search.dir/connectedList.c.obj
Binary_search.exe: CMakeFiles/Binary_search.dir/build.make
Binary_search.exe: CMakeFiles/Binary_search.dir/linklibs.rsp
Binary_search.exe: CMakeFiles/Binary_search.dir/objects1.rsp
Binary_search.exe: CMakeFiles/Binary_search.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\John\Dropbox\MTM HW files\C HW 3\K's files\MTMex3\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable Binary_search.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Binary_search.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Binary_search.dir/build: Binary_search.exe

.PHONY : CMakeFiles/Binary_search.dir/build

CMakeFiles/Binary_search.dir/requires: CMakeFiles/Binary_search.dir/binary_search.c.obj.requires
CMakeFiles/Binary_search.dir/requires: CMakeFiles/Binary_search.dir/connectedList.c.obj.requires

.PHONY : CMakeFiles/Binary_search.dir/requires

CMakeFiles/Binary_search.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Binary_search.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Binary_search.dir/clean

CMakeFiles/Binary_search.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\John\Dropbox\MTM HW files\C HW 3\K's files\MTMex3" "C:\Users\John\Dropbox\MTM HW files\C HW 3\K's files\MTMex3" "C:\Users\John\Dropbox\MTM HW files\C HW 3\K's files\MTMex3\cmake-build-debug" "C:\Users\John\Dropbox\MTM HW files\C HW 3\K's files\MTMex3\cmake-build-debug" "C:\Users\John\Dropbox\MTM HW files\C HW 3\K's files\MTMex3\cmake-build-debug\CMakeFiles\Binary_search.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Binary_search.dir/depend
