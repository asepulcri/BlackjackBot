# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/asepulcri/Documents/BlackjackBot

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/asepulcri/Documents/BlackjackBot

# Include any dependencies generated for this target.
include CMakeFiles/BlackjackBot.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/BlackjackBot.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/BlackjackBot.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/BlackjackBot.dir/flags.make

CMakeFiles/BlackjackBot.dir/source/card.cpp.o: CMakeFiles/BlackjackBot.dir/flags.make
CMakeFiles/BlackjackBot.dir/source/card.cpp.o: source/card.cpp
CMakeFiles/BlackjackBot.dir/source/card.cpp.o: CMakeFiles/BlackjackBot.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/asepulcri/Documents/BlackjackBot/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/BlackjackBot.dir/source/card.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/BlackjackBot.dir/source/card.cpp.o -MF CMakeFiles/BlackjackBot.dir/source/card.cpp.o.d -o CMakeFiles/BlackjackBot.dir/source/card.cpp.o -c /home/asepulcri/Documents/BlackjackBot/source/card.cpp

CMakeFiles/BlackjackBot.dir/source/card.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/BlackjackBot.dir/source/card.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/asepulcri/Documents/BlackjackBot/source/card.cpp > CMakeFiles/BlackjackBot.dir/source/card.cpp.i

CMakeFiles/BlackjackBot.dir/source/card.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/BlackjackBot.dir/source/card.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/asepulcri/Documents/BlackjackBot/source/card.cpp -o CMakeFiles/BlackjackBot.dir/source/card.cpp.s

CMakeFiles/BlackjackBot.dir/source/player.cpp.o: CMakeFiles/BlackjackBot.dir/flags.make
CMakeFiles/BlackjackBot.dir/source/player.cpp.o: source/player.cpp
CMakeFiles/BlackjackBot.dir/source/player.cpp.o: CMakeFiles/BlackjackBot.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/asepulcri/Documents/BlackjackBot/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/BlackjackBot.dir/source/player.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/BlackjackBot.dir/source/player.cpp.o -MF CMakeFiles/BlackjackBot.dir/source/player.cpp.o.d -o CMakeFiles/BlackjackBot.dir/source/player.cpp.o -c /home/asepulcri/Documents/BlackjackBot/source/player.cpp

CMakeFiles/BlackjackBot.dir/source/player.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/BlackjackBot.dir/source/player.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/asepulcri/Documents/BlackjackBot/source/player.cpp > CMakeFiles/BlackjackBot.dir/source/player.cpp.i

CMakeFiles/BlackjackBot.dir/source/player.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/BlackjackBot.dir/source/player.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/asepulcri/Documents/BlackjackBot/source/player.cpp -o CMakeFiles/BlackjackBot.dir/source/player.cpp.s

CMakeFiles/BlackjackBot.dir/source/shoe.cpp.o: CMakeFiles/BlackjackBot.dir/flags.make
CMakeFiles/BlackjackBot.dir/source/shoe.cpp.o: source/shoe.cpp
CMakeFiles/BlackjackBot.dir/source/shoe.cpp.o: CMakeFiles/BlackjackBot.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/asepulcri/Documents/BlackjackBot/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/BlackjackBot.dir/source/shoe.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/BlackjackBot.dir/source/shoe.cpp.o -MF CMakeFiles/BlackjackBot.dir/source/shoe.cpp.o.d -o CMakeFiles/BlackjackBot.dir/source/shoe.cpp.o -c /home/asepulcri/Documents/BlackjackBot/source/shoe.cpp

CMakeFiles/BlackjackBot.dir/source/shoe.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/BlackjackBot.dir/source/shoe.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/asepulcri/Documents/BlackjackBot/source/shoe.cpp > CMakeFiles/BlackjackBot.dir/source/shoe.cpp.i

CMakeFiles/BlackjackBot.dir/source/shoe.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/BlackjackBot.dir/source/shoe.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/asepulcri/Documents/BlackjackBot/source/shoe.cpp -o CMakeFiles/BlackjackBot.dir/source/shoe.cpp.s

# Object files for target BlackjackBot
BlackjackBot_OBJECTS = \
"CMakeFiles/BlackjackBot.dir/source/card.cpp.o" \
"CMakeFiles/BlackjackBot.dir/source/player.cpp.o" \
"CMakeFiles/BlackjackBot.dir/source/shoe.cpp.o"

# External object files for target BlackjackBot
BlackjackBot_EXTERNAL_OBJECTS =

libBlackjackBot.a: CMakeFiles/BlackjackBot.dir/source/card.cpp.o
libBlackjackBot.a: CMakeFiles/BlackjackBot.dir/source/player.cpp.o
libBlackjackBot.a: CMakeFiles/BlackjackBot.dir/source/shoe.cpp.o
libBlackjackBot.a: CMakeFiles/BlackjackBot.dir/build.make
libBlackjackBot.a: CMakeFiles/BlackjackBot.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/asepulcri/Documents/BlackjackBot/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX static library libBlackjackBot.a"
	$(CMAKE_COMMAND) -P CMakeFiles/BlackjackBot.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/BlackjackBot.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/BlackjackBot.dir/build: libBlackjackBot.a
.PHONY : CMakeFiles/BlackjackBot.dir/build

CMakeFiles/BlackjackBot.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/BlackjackBot.dir/cmake_clean.cmake
.PHONY : CMakeFiles/BlackjackBot.dir/clean

CMakeFiles/BlackjackBot.dir/depend:
	cd /home/asepulcri/Documents/BlackjackBot && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/asepulcri/Documents/BlackjackBot /home/asepulcri/Documents/BlackjackBot /home/asepulcri/Documents/BlackjackBot /home/asepulcri/Documents/BlackjackBot /home/asepulcri/Documents/BlackjackBot/CMakeFiles/BlackjackBot.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/BlackjackBot.dir/depend
