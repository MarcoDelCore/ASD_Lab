# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2021.2.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2021.2.3\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\ASUS\Desktop\PoliTo\II Anno\I Semestre\Algoritmi e Strutture Dati\Projects\L02\E03"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\ASUS\Desktop\PoliTo\II Anno\I Semestre\Algoritmi e Strutture Dati\Projects\L02\E03\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/E03.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/E03.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/E03.dir/flags.make

CMakeFiles/E03.dir/main.c.obj: CMakeFiles/E03.dir/flags.make
CMakeFiles/E03.dir/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\ASUS\Desktop\PoliTo\II Anno\I Semestre\Algoritmi e Strutture Dati\Projects\L02\E03\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/E03.dir/main.c.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-W\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\E03.dir\main.c.obj -c "C:\Users\ASUS\Desktop\PoliTo\II Anno\I Semestre\Algoritmi e Strutture Dati\Projects\L02\E03\main.c"

CMakeFiles/E03.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/E03.dir/main.c.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-W\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\Users\ASUS\Desktop\PoliTo\II Anno\I Semestre\Algoritmi e Strutture Dati\Projects\L02\E03\main.c" > CMakeFiles\E03.dir\main.c.i

CMakeFiles/E03.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/E03.dir/main.c.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-W\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:\Users\ASUS\Desktop\PoliTo\II Anno\I Semestre\Algoritmi e Strutture Dati\Projects\L02\E03\main.c" -o CMakeFiles\E03.dir\main.c.s

# Object files for target E03
E03_OBJECTS = \
"CMakeFiles/E03.dir/main.c.obj"

# External object files for target E03
E03_EXTERNAL_OBJECTS =

E03.exe: CMakeFiles/E03.dir/main.c.obj
E03.exe: CMakeFiles/E03.dir/build.make
E03.exe: CMakeFiles/E03.dir/linklibs.rsp
E03.exe: CMakeFiles/E03.dir/objects1.rsp
E03.exe: CMakeFiles/E03.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\ASUS\Desktop\PoliTo\II Anno\I Semestre\Algoritmi e Strutture Dati\Projects\L02\E03\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable E03.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\E03.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/E03.dir/build: E03.exe
.PHONY : CMakeFiles/E03.dir/build

CMakeFiles/E03.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\E03.dir\cmake_clean.cmake
.PHONY : CMakeFiles/E03.dir/clean

CMakeFiles/E03.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\ASUS\Desktop\PoliTo\II Anno\I Semestre\Algoritmi e Strutture Dati\Projects\L02\E03" "C:\Users\ASUS\Desktop\PoliTo\II Anno\I Semestre\Algoritmi e Strutture Dati\Projects\L02\E03" "C:\Users\ASUS\Desktop\PoliTo\II Anno\I Semestre\Algoritmi e Strutture Dati\Projects\L02\E03\cmake-build-debug" "C:\Users\ASUS\Desktop\PoliTo\II Anno\I Semestre\Algoritmi e Strutture Dati\Projects\L02\E03\cmake-build-debug" "C:\Users\ASUS\Desktop\PoliTo\II Anno\I Semestre\Algoritmi e Strutture Dati\Projects\L02\E03\cmake-build-debug\CMakeFiles\E03.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/E03.dir/depend

