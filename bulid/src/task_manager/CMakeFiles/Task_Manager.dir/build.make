# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.30

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
CMAKE_COMMAND = E:\CMake\bin\cmake.exe

# The command to remove a file.
RM = E:\CMake\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\vscode_c\data_structure\lab01

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\vscode_c\data_structure\lab01\bulid

# Include any dependencies generated for this target.
include src/task_manager/CMakeFiles/Task_Manager.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/task_manager/CMakeFiles/Task_Manager.dir/compiler_depend.make

# Include the progress variables for this target.
include src/task_manager/CMakeFiles/Task_Manager.dir/progress.make

# Include the compile flags for this target's objects.
include src/task_manager/CMakeFiles/Task_Manager.dir/flags.make

src/task_manager/Task_Manager_autogen/timestamp: E:/Qt/6.7.2/mingw_64/./bin/moc.exe
src/task_manager/Task_Manager_autogen/timestamp: E:/Qt/6.7.2/mingw_64/./bin/uic.exe
src/task_manager/Task_Manager_autogen/timestamp: src/task_manager/CMakeFiles/Task_Manager.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=D:\vscode_c\data_structure\lab01\bulid\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target Task_Manager"
	cd /d D:\vscode_c\data_structure\lab01\bulid\src\task_manager && E:\CMake\bin\cmake.exe -E cmake_autogen D:/vscode_c/data_structure/lab01/bulid/src/task_manager/CMakeFiles/Task_Manager_autogen.dir/AutogenInfo.json Debug
	cd /d D:\vscode_c\data_structure\lab01\bulid\src\task_manager && E:\CMake\bin\cmake.exe -E touch D:/vscode_c/data_structure/lab01/bulid/src/task_manager/Task_Manager_autogen/timestamp

src/task_manager/CMakeFiles/Task_Manager.dir/Task_Manager_autogen/mocs_compilation.cpp.obj: src/task_manager/CMakeFiles/Task_Manager.dir/flags.make
src/task_manager/CMakeFiles/Task_Manager.dir/Task_Manager_autogen/mocs_compilation.cpp.obj: src/task_manager/CMakeFiles/Task_Manager.dir/includes_CXX.rsp
src/task_manager/CMakeFiles/Task_Manager.dir/Task_Manager_autogen/mocs_compilation.cpp.obj: src/task_manager/Task_Manager_autogen/mocs_compilation.cpp
src/task_manager/CMakeFiles/Task_Manager.dir/Task_Manager_autogen/mocs_compilation.cpp.obj: src/task_manager/CMakeFiles/Task_Manager.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\vscode_c\data_structure\lab01\bulid\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/task_manager/CMakeFiles/Task_Manager.dir/Task_Manager_autogen/mocs_compilation.cpp.obj"
	cd /d D:\vscode_c\data_structure\lab01\bulid\src\task_manager && E:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/task_manager/CMakeFiles/Task_Manager.dir/Task_Manager_autogen/mocs_compilation.cpp.obj -MF CMakeFiles\Task_Manager.dir\Task_Manager_autogen\mocs_compilation.cpp.obj.d -o CMakeFiles\Task_Manager.dir\Task_Manager_autogen\mocs_compilation.cpp.obj -c D:\vscode_c\data_structure\lab01\bulid\src\task_manager\Task_Manager_autogen\mocs_compilation.cpp

src/task_manager/CMakeFiles/Task_Manager.dir/Task_Manager_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Task_Manager.dir/Task_Manager_autogen/mocs_compilation.cpp.i"
	cd /d D:\vscode_c\data_structure\lab01\bulid\src\task_manager && E:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\vscode_c\data_structure\lab01\bulid\src\task_manager\Task_Manager_autogen\mocs_compilation.cpp > CMakeFiles\Task_Manager.dir\Task_Manager_autogen\mocs_compilation.cpp.i

src/task_manager/CMakeFiles/Task_Manager.dir/Task_Manager_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Task_Manager.dir/Task_Manager_autogen/mocs_compilation.cpp.s"
	cd /d D:\vscode_c\data_structure\lab01\bulid\src\task_manager && E:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\vscode_c\data_structure\lab01\bulid\src\task_manager\Task_Manager_autogen\mocs_compilation.cpp -o CMakeFiles\Task_Manager.dir\Task_Manager_autogen\mocs_compilation.cpp.s

src/task_manager/CMakeFiles/Task_Manager.dir/LinkList.cpp.obj: src/task_manager/CMakeFiles/Task_Manager.dir/flags.make
src/task_manager/CMakeFiles/Task_Manager.dir/LinkList.cpp.obj: src/task_manager/CMakeFiles/Task_Manager.dir/includes_CXX.rsp
src/task_manager/CMakeFiles/Task_Manager.dir/LinkList.cpp.obj: D:/vscode_c/data_structure/lab01/src/task_manager/LinkList.cpp
src/task_manager/CMakeFiles/Task_Manager.dir/LinkList.cpp.obj: src/task_manager/CMakeFiles/Task_Manager.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\vscode_c\data_structure\lab01\bulid\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/task_manager/CMakeFiles/Task_Manager.dir/LinkList.cpp.obj"
	cd /d D:\vscode_c\data_structure\lab01\bulid\src\task_manager && E:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/task_manager/CMakeFiles/Task_Manager.dir/LinkList.cpp.obj -MF CMakeFiles\Task_Manager.dir\LinkList.cpp.obj.d -o CMakeFiles\Task_Manager.dir\LinkList.cpp.obj -c D:\vscode_c\data_structure\lab01\src\task_manager\LinkList.cpp

src/task_manager/CMakeFiles/Task_Manager.dir/LinkList.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/Task_Manager.dir/LinkList.cpp.i"
	cd /d D:\vscode_c\data_structure\lab01\bulid\src\task_manager && E:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\vscode_c\data_structure\lab01\src\task_manager\LinkList.cpp > CMakeFiles\Task_Manager.dir\LinkList.cpp.i

src/task_manager/CMakeFiles/Task_Manager.dir/LinkList.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/Task_Manager.dir/LinkList.cpp.s"
	cd /d D:\vscode_c\data_structure\lab01\bulid\src\task_manager && E:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\vscode_c\data_structure\lab01\src\task_manager\LinkList.cpp -o CMakeFiles\Task_Manager.dir\LinkList.cpp.s

# Object files for target Task_Manager
Task_Manager_OBJECTS = \
"CMakeFiles/Task_Manager.dir/Task_Manager_autogen/mocs_compilation.cpp.obj" \
"CMakeFiles/Task_Manager.dir/LinkList.cpp.obj"

# External object files for target Task_Manager
Task_Manager_EXTERNAL_OBJECTS =

src/task_manager/libTask_Manager.a: src/task_manager/CMakeFiles/Task_Manager.dir/Task_Manager_autogen/mocs_compilation.cpp.obj
src/task_manager/libTask_Manager.a: src/task_manager/CMakeFiles/Task_Manager.dir/LinkList.cpp.obj
src/task_manager/libTask_Manager.a: src/task_manager/CMakeFiles/Task_Manager.dir/build.make
src/task_manager/libTask_Manager.a: src/task_manager/CMakeFiles/Task_Manager.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=D:\vscode_c\data_structure\lab01\bulid\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX static library libTask_Manager.a"
	cd /d D:\vscode_c\data_structure\lab01\bulid\src\task_manager && $(CMAKE_COMMAND) -P CMakeFiles\Task_Manager.dir\cmake_clean_target.cmake
	cd /d D:\vscode_c\data_structure\lab01\bulid\src\task_manager && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Task_Manager.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/task_manager/CMakeFiles/Task_Manager.dir/build: src/task_manager/libTask_Manager.a
.PHONY : src/task_manager/CMakeFiles/Task_Manager.dir/build

src/task_manager/CMakeFiles/Task_Manager.dir/clean:
	cd /d D:\vscode_c\data_structure\lab01\bulid\src\task_manager && $(CMAKE_COMMAND) -P CMakeFiles\Task_Manager.dir\cmake_clean.cmake
.PHONY : src/task_manager/CMakeFiles/Task_Manager.dir/clean

src/task_manager/CMakeFiles/Task_Manager.dir/depend: src/task_manager/Task_Manager_autogen/timestamp
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\vscode_c\data_structure\lab01 D:\vscode_c\data_structure\lab01\src\task_manager D:\vscode_c\data_structure\lab01\bulid D:\vscode_c\data_structure\lab01\bulid\src\task_manager D:\vscode_c\data_structure\lab01\bulid\src\task_manager\CMakeFiles\Task_Manager.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : src/task_manager/CMakeFiles/Task_Manager.dir/depend

