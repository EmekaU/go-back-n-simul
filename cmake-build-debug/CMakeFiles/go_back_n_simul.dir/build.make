# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/umeozoemeka/Desktop/CMPT_434/Assignments/go-back-n-simul

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/umeozoemeka/Desktop/CMPT_434/Assignments/go-back-n-simul/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/go_back_n_simul.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/go_back_n_simul.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/go_back_n_simul.dir/flags.make

CMakeFiles/go_back_n_simul.dir/common.c.o: CMakeFiles/go_back_n_simul.dir/flags.make
CMakeFiles/go_back_n_simul.dir/common.c.o: ../common.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/umeozoemeka/Desktop/CMPT_434/Assignments/go-back-n-simul/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/go_back_n_simul.dir/common.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/go_back_n_simul.dir/common.c.o -c /Users/umeozoemeka/Desktop/CMPT_434/Assignments/go-back-n-simul/common.c

CMakeFiles/go_back_n_simul.dir/common.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/go_back_n_simul.dir/common.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/umeozoemeka/Desktop/CMPT_434/Assignments/go-back-n-simul/common.c > CMakeFiles/go_back_n_simul.dir/common.c.i

CMakeFiles/go_back_n_simul.dir/common.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/go_back_n_simul.dir/common.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/umeozoemeka/Desktop/CMPT_434/Assignments/go-back-n-simul/common.c -o CMakeFiles/go_back_n_simul.dir/common.c.s

CMakeFiles/go_back_n_simul.dir/receiver.c.o: CMakeFiles/go_back_n_simul.dir/flags.make
CMakeFiles/go_back_n_simul.dir/receiver.c.o: ../receiver.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/umeozoemeka/Desktop/CMPT_434/Assignments/go-back-n-simul/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/go_back_n_simul.dir/receiver.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/go_back_n_simul.dir/receiver.c.o -c /Users/umeozoemeka/Desktop/CMPT_434/Assignments/go-back-n-simul/receiver.c

CMakeFiles/go_back_n_simul.dir/receiver.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/go_back_n_simul.dir/receiver.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/umeozoemeka/Desktop/CMPT_434/Assignments/go-back-n-simul/receiver.c > CMakeFiles/go_back_n_simul.dir/receiver.c.i

CMakeFiles/go_back_n_simul.dir/receiver.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/go_back_n_simul.dir/receiver.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/umeozoemeka/Desktop/CMPT_434/Assignments/go-back-n-simul/receiver.c -o CMakeFiles/go_back_n_simul.dir/receiver.c.s

CMakeFiles/go_back_n_simul.dir/sender.c.o: CMakeFiles/go_back_n_simul.dir/flags.make
CMakeFiles/go_back_n_simul.dir/sender.c.o: ../sender.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/umeozoemeka/Desktop/CMPT_434/Assignments/go-back-n-simul/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/go_back_n_simul.dir/sender.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/go_back_n_simul.dir/sender.c.o -c /Users/umeozoemeka/Desktop/CMPT_434/Assignments/go-back-n-simul/sender.c

CMakeFiles/go_back_n_simul.dir/sender.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/go_back_n_simul.dir/sender.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/umeozoemeka/Desktop/CMPT_434/Assignments/go-back-n-simul/sender.c > CMakeFiles/go_back_n_simul.dir/sender.c.i

CMakeFiles/go_back_n_simul.dir/sender.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/go_back_n_simul.dir/sender.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/umeozoemeka/Desktop/CMPT_434/Assignments/go-back-n-simul/sender.c -o CMakeFiles/go_back_n_simul.dir/sender.c.s

# Object files for target go_back_n_simul
go_back_n_simul_OBJECTS = \
"CMakeFiles/go_back_n_simul.dir/common.c.o" \
"CMakeFiles/go_back_n_simul.dir/receiver.c.o" \
"CMakeFiles/go_back_n_simul.dir/sender.c.o"

# External object files for target go_back_n_simul
go_back_n_simul_EXTERNAL_OBJECTS =

go_back_n_simul: CMakeFiles/go_back_n_simul.dir/common.c.o
go_back_n_simul: CMakeFiles/go_back_n_simul.dir/receiver.c.o
go_back_n_simul: CMakeFiles/go_back_n_simul.dir/sender.c.o
go_back_n_simul: CMakeFiles/go_back_n_simul.dir/build.make
go_back_n_simul: CMakeFiles/go_back_n_simul.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/umeozoemeka/Desktop/CMPT_434/Assignments/go-back-n-simul/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable go_back_n_simul"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/go_back_n_simul.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/go_back_n_simul.dir/build: go_back_n_simul
.PHONY : CMakeFiles/go_back_n_simul.dir/build

CMakeFiles/go_back_n_simul.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/go_back_n_simul.dir/cmake_clean.cmake
.PHONY : CMakeFiles/go_back_n_simul.dir/clean

CMakeFiles/go_back_n_simul.dir/depend:
	cd /Users/umeozoemeka/Desktop/CMPT_434/Assignments/go-back-n-simul/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/umeozoemeka/Desktop/CMPT_434/Assignments/go-back-n-simul /Users/umeozoemeka/Desktop/CMPT_434/Assignments/go-back-n-simul /Users/umeozoemeka/Desktop/CMPT_434/Assignments/go-back-n-simul/cmake-build-debug /Users/umeozoemeka/Desktop/CMPT_434/Assignments/go-back-n-simul/cmake-build-debug /Users/umeozoemeka/Desktop/CMPT_434/Assignments/go-back-n-simul/cmake-build-debug/CMakeFiles/go_back_n_simul.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/go_back_n_simul.dir/depend

