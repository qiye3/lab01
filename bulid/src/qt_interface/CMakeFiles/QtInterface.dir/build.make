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
include src/qt_interface/CMakeFiles/QtInterface.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/qt_interface/CMakeFiles/QtInterface.dir/compiler_depend.make

# Include the progress variables for this target.
include src/qt_interface/CMakeFiles/QtInterface.dir/progress.make

# Include the compile flags for this target's objects.
include src/qt_interface/CMakeFiles/QtInterface.dir/flags.make

src/qt_interface/QtInterface_autogen/timestamp: E:/Qt/6.7.2/mingw_64/./bin/moc.exe
src/qt_interface/QtInterface_autogen/timestamp: E:/Qt/6.7.2/mingw_64/./bin/uic.exe
src/qt_interface/QtInterface_autogen/timestamp: src/qt_interface/CMakeFiles/QtInterface.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=D:\vscode_c\data_structure\lab01\bulid\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target QtInterface"
	cd /d D:\vscode_c\data_structure\lab01\bulid\src\qt_interface && E:\CMake\bin\cmake.exe -E cmake_autogen D:/vscode_c/data_structure/lab01/bulid/src/qt_interface/CMakeFiles/QtInterface_autogen.dir/AutogenInfo.json Debug
	cd /d D:\vscode_c\data_structure\lab01\bulid\src\qt_interface && E:\CMake\bin\cmake.exe -E touch D:/vscode_c/data_structure/lab01/bulid/src/qt_interface/QtInterface_autogen/timestamp

src/qt_interface/CMakeFiles/QtInterface.dir/QtInterface_autogen/mocs_compilation.cpp.obj: src/qt_interface/CMakeFiles/QtInterface.dir/flags.make
src/qt_interface/CMakeFiles/QtInterface.dir/QtInterface_autogen/mocs_compilation.cpp.obj: src/qt_interface/CMakeFiles/QtInterface.dir/includes_CXX.rsp
src/qt_interface/CMakeFiles/QtInterface.dir/QtInterface_autogen/mocs_compilation.cpp.obj: src/qt_interface/QtInterface_autogen/mocs_compilation.cpp
src/qt_interface/CMakeFiles/QtInterface.dir/QtInterface_autogen/mocs_compilation.cpp.obj: src/qt_interface/CMakeFiles/QtInterface.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\vscode_c\data_structure\lab01\bulid\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/qt_interface/CMakeFiles/QtInterface.dir/QtInterface_autogen/mocs_compilation.cpp.obj"
	cd /d D:\vscode_c\data_structure\lab01\bulid\src\qt_interface && E:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/qt_interface/CMakeFiles/QtInterface.dir/QtInterface_autogen/mocs_compilation.cpp.obj -MF CMakeFiles\QtInterface.dir\QtInterface_autogen\mocs_compilation.cpp.obj.d -o CMakeFiles\QtInterface.dir\QtInterface_autogen\mocs_compilation.cpp.obj -c D:\vscode_c\data_structure\lab01\bulid\src\qt_interface\QtInterface_autogen\mocs_compilation.cpp

src/qt_interface/CMakeFiles/QtInterface.dir/QtInterface_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/QtInterface.dir/QtInterface_autogen/mocs_compilation.cpp.i"
	cd /d D:\vscode_c\data_structure\lab01\bulid\src\qt_interface && E:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\vscode_c\data_structure\lab01\bulid\src\qt_interface\QtInterface_autogen\mocs_compilation.cpp > CMakeFiles\QtInterface.dir\QtInterface_autogen\mocs_compilation.cpp.i

src/qt_interface/CMakeFiles/QtInterface.dir/QtInterface_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/QtInterface.dir/QtInterface_autogen/mocs_compilation.cpp.s"
	cd /d D:\vscode_c\data_structure\lab01\bulid\src\qt_interface && E:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\vscode_c\data_structure\lab01\bulid\src\qt_interface\QtInterface_autogen\mocs_compilation.cpp -o CMakeFiles\QtInterface.dir\QtInterface_autogen\mocs_compilation.cpp.s

src/qt_interface/CMakeFiles/QtInterface.dir/mainwindow.cpp.obj: src/qt_interface/CMakeFiles/QtInterface.dir/flags.make
src/qt_interface/CMakeFiles/QtInterface.dir/mainwindow.cpp.obj: src/qt_interface/CMakeFiles/QtInterface.dir/includes_CXX.rsp
src/qt_interface/CMakeFiles/QtInterface.dir/mainwindow.cpp.obj: D:/vscode_c/data_structure/lab01/src/qt_interface/mainwindow.cpp
src/qt_interface/CMakeFiles/QtInterface.dir/mainwindow.cpp.obj: src/qt_interface/CMakeFiles/QtInterface.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\vscode_c\data_structure\lab01\bulid\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/qt_interface/CMakeFiles/QtInterface.dir/mainwindow.cpp.obj"
	cd /d D:\vscode_c\data_structure\lab01\bulid\src\qt_interface && E:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/qt_interface/CMakeFiles/QtInterface.dir/mainwindow.cpp.obj -MF CMakeFiles\QtInterface.dir\mainwindow.cpp.obj.d -o CMakeFiles\QtInterface.dir\mainwindow.cpp.obj -c D:\vscode_c\data_structure\lab01\src\qt_interface\mainwindow.cpp

src/qt_interface/CMakeFiles/QtInterface.dir/mainwindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/QtInterface.dir/mainwindow.cpp.i"
	cd /d D:\vscode_c\data_structure\lab01\bulid\src\qt_interface && E:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\vscode_c\data_structure\lab01\src\qt_interface\mainwindow.cpp > CMakeFiles\QtInterface.dir\mainwindow.cpp.i

src/qt_interface/CMakeFiles/QtInterface.dir/mainwindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/QtInterface.dir/mainwindow.cpp.s"
	cd /d D:\vscode_c\data_structure\lab01\bulid\src\qt_interface && E:\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\vscode_c\data_structure\lab01\src\qt_interface\mainwindow.cpp -o CMakeFiles\QtInterface.dir\mainwindow.cpp.s

# Object files for target QtInterface
QtInterface_OBJECTS = \
"CMakeFiles/QtInterface.dir/QtInterface_autogen/mocs_compilation.cpp.obj" \
"CMakeFiles/QtInterface.dir/mainwindow.cpp.obj"

# External object files for target QtInterface
QtInterface_EXTERNAL_OBJECTS =

src/qt_interface/libQtInterface.a: src/qt_interface/CMakeFiles/QtInterface.dir/QtInterface_autogen/mocs_compilation.cpp.obj
src/qt_interface/libQtInterface.a: src/qt_interface/CMakeFiles/QtInterface.dir/mainwindow.cpp.obj
src/qt_interface/libQtInterface.a: src/qt_interface/CMakeFiles/QtInterface.dir/build.make
src/qt_interface/libQtInterface.a: src/qt_interface/CMakeFiles/QtInterface.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=D:\vscode_c\data_structure\lab01\bulid\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX static library libQtInterface.a"
	cd /d D:\vscode_c\data_structure\lab01\bulid\src\qt_interface && $(CMAKE_COMMAND) -P CMakeFiles\QtInterface.dir\cmake_clean_target.cmake
	cd /d D:\vscode_c\data_structure\lab01\bulid\src\qt_interface && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\QtInterface.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/qt_interface/CMakeFiles/QtInterface.dir/build: src/qt_interface/libQtInterface.a
.PHONY : src/qt_interface/CMakeFiles/QtInterface.dir/build

src/qt_interface/CMakeFiles/QtInterface.dir/clean:
	cd /d D:\vscode_c\data_structure\lab01\bulid\src\qt_interface && $(CMAKE_COMMAND) -P CMakeFiles\QtInterface.dir\cmake_clean.cmake
.PHONY : src/qt_interface/CMakeFiles/QtInterface.dir/clean

src/qt_interface/CMakeFiles/QtInterface.dir/depend: src/qt_interface/QtInterface_autogen/timestamp
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\vscode_c\data_structure\lab01 D:\vscode_c\data_structure\lab01\src\qt_interface D:\vscode_c\data_structure\lab01\bulid D:\vscode_c\data_structure\lab01\bulid\src\qt_interface D:\vscode_c\data_structure\lab01\bulid\src\qt_interface\CMakeFiles\QtInterface.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : src/qt_interface/CMakeFiles/QtInterface.dir/depend

