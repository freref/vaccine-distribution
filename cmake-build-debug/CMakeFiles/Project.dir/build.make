# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/frederic/Documents/Informatica/Sem2/PSE/Project

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/frederic/Documents/Informatica/Sem2/PSE/Project/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Project.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Project.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Project.dir/flags.make

CMakeFiles/Project.dir/main.cpp.o: CMakeFiles/Project.dir/flags.make
CMakeFiles/Project.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/frederic/Documents/Informatica/Sem2/PSE/Project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Project.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Project.dir/main.cpp.o -c /Users/frederic/Documents/Informatica/Sem2/PSE/Project/main.cpp

CMakeFiles/Project.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Project.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/frederic/Documents/Informatica/Sem2/PSE/Project/main.cpp > CMakeFiles/Project.dir/main.cpp.i

CMakeFiles/Project.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Project.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/frederic/Documents/Informatica/Sem2/PSE/Project/main.cpp -o CMakeFiles/Project.dir/main.cpp.s

CMakeFiles/Project.dir/XmlParser/tinystr.cpp.o: CMakeFiles/Project.dir/flags.make
CMakeFiles/Project.dir/XmlParser/tinystr.cpp.o: ../XmlParser/tinystr.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/frederic/Documents/Informatica/Sem2/PSE/Project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Project.dir/XmlParser/tinystr.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Project.dir/XmlParser/tinystr.cpp.o -c /Users/frederic/Documents/Informatica/Sem2/PSE/Project/XmlParser/tinystr.cpp

CMakeFiles/Project.dir/XmlParser/tinystr.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Project.dir/XmlParser/tinystr.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/frederic/Documents/Informatica/Sem2/PSE/Project/XmlParser/tinystr.cpp > CMakeFiles/Project.dir/XmlParser/tinystr.cpp.i

CMakeFiles/Project.dir/XmlParser/tinystr.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Project.dir/XmlParser/tinystr.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/frederic/Documents/Informatica/Sem2/PSE/Project/XmlParser/tinystr.cpp -o CMakeFiles/Project.dir/XmlParser/tinystr.cpp.s

CMakeFiles/Project.dir/XmlParser/tinyxml.cpp.o: CMakeFiles/Project.dir/flags.make
CMakeFiles/Project.dir/XmlParser/tinyxml.cpp.o: ../XmlParser/tinyxml.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/frederic/Documents/Informatica/Sem2/PSE/Project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Project.dir/XmlParser/tinyxml.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Project.dir/XmlParser/tinyxml.cpp.o -c /Users/frederic/Documents/Informatica/Sem2/PSE/Project/XmlParser/tinyxml.cpp

CMakeFiles/Project.dir/XmlParser/tinyxml.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Project.dir/XmlParser/tinyxml.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/frederic/Documents/Informatica/Sem2/PSE/Project/XmlParser/tinyxml.cpp > CMakeFiles/Project.dir/XmlParser/tinyxml.cpp.i

CMakeFiles/Project.dir/XmlParser/tinyxml.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Project.dir/XmlParser/tinyxml.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/frederic/Documents/Informatica/Sem2/PSE/Project/XmlParser/tinyxml.cpp -o CMakeFiles/Project.dir/XmlParser/tinyxml.cpp.s

CMakeFiles/Project.dir/XmlParser/tinyxmlerror.cpp.o: CMakeFiles/Project.dir/flags.make
CMakeFiles/Project.dir/XmlParser/tinyxmlerror.cpp.o: ../XmlParser/tinyxmlerror.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/frederic/Documents/Informatica/Sem2/PSE/Project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Project.dir/XmlParser/tinyxmlerror.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Project.dir/XmlParser/tinyxmlerror.cpp.o -c /Users/frederic/Documents/Informatica/Sem2/PSE/Project/XmlParser/tinyxmlerror.cpp

CMakeFiles/Project.dir/XmlParser/tinyxmlerror.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Project.dir/XmlParser/tinyxmlerror.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/frederic/Documents/Informatica/Sem2/PSE/Project/XmlParser/tinyxmlerror.cpp > CMakeFiles/Project.dir/XmlParser/tinyxmlerror.cpp.i

CMakeFiles/Project.dir/XmlParser/tinyxmlerror.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Project.dir/XmlParser/tinyxmlerror.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/frederic/Documents/Informatica/Sem2/PSE/Project/XmlParser/tinyxmlerror.cpp -o CMakeFiles/Project.dir/XmlParser/tinyxmlerror.cpp.s

CMakeFiles/Project.dir/XmlParser/tinyxmlparser.cpp.o: CMakeFiles/Project.dir/flags.make
CMakeFiles/Project.dir/XmlParser/tinyxmlparser.cpp.o: ../XmlParser/tinyxmlparser.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/frederic/Documents/Informatica/Sem2/PSE/Project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/Project.dir/XmlParser/tinyxmlparser.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Project.dir/XmlParser/tinyxmlparser.cpp.o -c /Users/frederic/Documents/Informatica/Sem2/PSE/Project/XmlParser/tinyxmlparser.cpp

CMakeFiles/Project.dir/XmlParser/tinyxmlparser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Project.dir/XmlParser/tinyxmlparser.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/frederic/Documents/Informatica/Sem2/PSE/Project/XmlParser/tinyxmlparser.cpp > CMakeFiles/Project.dir/XmlParser/tinyxmlparser.cpp.i

CMakeFiles/Project.dir/XmlParser/tinyxmlparser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Project.dir/XmlParser/tinyxmlparser.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/frederic/Documents/Informatica/Sem2/PSE/Project/XmlParser/tinyxmlparser.cpp -o CMakeFiles/Project.dir/XmlParser/tinyxmlparser.cpp.s

CMakeFiles/Project.dir/Simulation/Hub.cpp.o: CMakeFiles/Project.dir/flags.make
CMakeFiles/Project.dir/Simulation/Hub.cpp.o: ../Simulation/Hub.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/frederic/Documents/Informatica/Sem2/PSE/Project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/Project.dir/Simulation/Hub.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Project.dir/Simulation/Hub.cpp.o -c /Users/frederic/Documents/Informatica/Sem2/PSE/Project/Simulation/Hub.cpp

CMakeFiles/Project.dir/Simulation/Hub.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Project.dir/Simulation/Hub.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/frederic/Documents/Informatica/Sem2/PSE/Project/Simulation/Hub.cpp > CMakeFiles/Project.dir/Simulation/Hub.cpp.i

CMakeFiles/Project.dir/Simulation/Hub.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Project.dir/Simulation/Hub.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/frederic/Documents/Informatica/Sem2/PSE/Project/Simulation/Hub.cpp -o CMakeFiles/Project.dir/Simulation/Hub.cpp.s

CMakeFiles/Project.dir/Simulation/Centrum.cpp.o: CMakeFiles/Project.dir/flags.make
CMakeFiles/Project.dir/Simulation/Centrum.cpp.o: ../Simulation/Centrum.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/frederic/Documents/Informatica/Sem2/PSE/Project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/Project.dir/Simulation/Centrum.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Project.dir/Simulation/Centrum.cpp.o -c /Users/frederic/Documents/Informatica/Sem2/PSE/Project/Simulation/Centrum.cpp

CMakeFiles/Project.dir/Simulation/Centrum.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Project.dir/Simulation/Centrum.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/frederic/Documents/Informatica/Sem2/PSE/Project/Simulation/Centrum.cpp > CMakeFiles/Project.dir/Simulation/Centrum.cpp.i

CMakeFiles/Project.dir/Simulation/Centrum.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Project.dir/Simulation/Centrum.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/frederic/Documents/Informatica/Sem2/PSE/Project/Simulation/Centrum.cpp -o CMakeFiles/Project.dir/Simulation/Centrum.cpp.s

CMakeFiles/Project.dir/Simulation/simulation.cpp.o: CMakeFiles/Project.dir/flags.make
CMakeFiles/Project.dir/Simulation/simulation.cpp.o: ../Simulation/simulation.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/frederic/Documents/Informatica/Sem2/PSE/Project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/Project.dir/Simulation/simulation.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Project.dir/Simulation/simulation.cpp.o -c /Users/frederic/Documents/Informatica/Sem2/PSE/Project/Simulation/simulation.cpp

CMakeFiles/Project.dir/Simulation/simulation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Project.dir/Simulation/simulation.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/frederic/Documents/Informatica/Sem2/PSE/Project/Simulation/simulation.cpp > CMakeFiles/Project.dir/Simulation/simulation.cpp.i

CMakeFiles/Project.dir/Simulation/simulation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Project.dir/Simulation/simulation.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/frederic/Documents/Informatica/Sem2/PSE/Project/Simulation/simulation.cpp -o CMakeFiles/Project.dir/Simulation/simulation.cpp.s

CMakeFiles/Project.dir/Simulation/simulationImporter.cpp.o: CMakeFiles/Project.dir/flags.make
CMakeFiles/Project.dir/Simulation/simulationImporter.cpp.o: ../Simulation/simulationImporter.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/frederic/Documents/Informatica/Sem2/PSE/Project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/Project.dir/Simulation/simulationImporter.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Project.dir/Simulation/simulationImporter.cpp.o -c /Users/frederic/Documents/Informatica/Sem2/PSE/Project/Simulation/simulationImporter.cpp

CMakeFiles/Project.dir/Simulation/simulationImporter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Project.dir/Simulation/simulationImporter.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/frederic/Documents/Informatica/Sem2/PSE/Project/Simulation/simulationImporter.cpp > CMakeFiles/Project.dir/Simulation/simulationImporter.cpp.i

CMakeFiles/Project.dir/Simulation/simulationImporter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Project.dir/Simulation/simulationImporter.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/frederic/Documents/Informatica/Sem2/PSE/Project/Simulation/simulationImporter.cpp -o CMakeFiles/Project.dir/Simulation/simulationImporter.cpp.s

CMakeFiles/Project.dir/Simulation/autoSim.cpp.o: CMakeFiles/Project.dir/flags.make
CMakeFiles/Project.dir/Simulation/autoSim.cpp.o: ../Simulation/autoSim.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/frederic/Documents/Informatica/Sem2/PSE/Project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/Project.dir/Simulation/autoSim.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Project.dir/Simulation/autoSim.cpp.o -c /Users/frederic/Documents/Informatica/Sem2/PSE/Project/Simulation/autoSim.cpp

CMakeFiles/Project.dir/Simulation/autoSim.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Project.dir/Simulation/autoSim.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/frederic/Documents/Informatica/Sem2/PSE/Project/Simulation/autoSim.cpp > CMakeFiles/Project.dir/Simulation/autoSim.cpp.i

CMakeFiles/Project.dir/Simulation/autoSim.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Project.dir/Simulation/autoSim.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/frederic/Documents/Informatica/Sem2/PSE/Project/Simulation/autoSim.cpp -o CMakeFiles/Project.dir/Simulation/autoSim.cpp.s

CMakeFiles/Project.dir/Simulation/fileCompare.cpp.o: CMakeFiles/Project.dir/flags.make
CMakeFiles/Project.dir/Simulation/fileCompare.cpp.o: ../Simulation/fileCompare.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/frederic/Documents/Informatica/Sem2/PSE/Project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/Project.dir/Simulation/fileCompare.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Project.dir/Simulation/fileCompare.cpp.o -c /Users/frederic/Documents/Informatica/Sem2/PSE/Project/Simulation/fileCompare.cpp

CMakeFiles/Project.dir/Simulation/fileCompare.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Project.dir/Simulation/fileCompare.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/frederic/Documents/Informatica/Sem2/PSE/Project/Simulation/fileCompare.cpp > CMakeFiles/Project.dir/Simulation/fileCompare.cpp.i

CMakeFiles/Project.dir/Simulation/fileCompare.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Project.dir/Simulation/fileCompare.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/frederic/Documents/Informatica/Sem2/PSE/Project/Simulation/fileCompare.cpp -o CMakeFiles/Project.dir/Simulation/fileCompare.cpp.s

CMakeFiles/Project.dir/Simulation/Vaccine.cpp.o: CMakeFiles/Project.dir/flags.make
CMakeFiles/Project.dir/Simulation/Vaccine.cpp.o: ../Simulation/Vaccine.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/frederic/Documents/Informatica/Sem2/PSE/Project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/Project.dir/Simulation/Vaccine.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Project.dir/Simulation/Vaccine.cpp.o -c /Users/frederic/Documents/Informatica/Sem2/PSE/Project/Simulation/Vaccine.cpp

CMakeFiles/Project.dir/Simulation/Vaccine.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Project.dir/Simulation/Vaccine.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/frederic/Documents/Informatica/Sem2/PSE/Project/Simulation/Vaccine.cpp > CMakeFiles/Project.dir/Simulation/Vaccine.cpp.i

CMakeFiles/Project.dir/Simulation/Vaccine.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Project.dir/Simulation/Vaccine.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/frederic/Documents/Informatica/Sem2/PSE/Project/Simulation/Vaccine.cpp -o CMakeFiles/Project.dir/Simulation/Vaccine.cpp.s

# Object files for target Project
Project_OBJECTS = \
"CMakeFiles/Project.dir/main.cpp.o" \
"CMakeFiles/Project.dir/XmlParser/tinystr.cpp.o" \
"CMakeFiles/Project.dir/XmlParser/tinyxml.cpp.o" \
"CMakeFiles/Project.dir/XmlParser/tinyxmlerror.cpp.o" \
"CMakeFiles/Project.dir/XmlParser/tinyxmlparser.cpp.o" \
"CMakeFiles/Project.dir/Simulation/Hub.cpp.o" \
"CMakeFiles/Project.dir/Simulation/Centrum.cpp.o" \
"CMakeFiles/Project.dir/Simulation/simulation.cpp.o" \
"CMakeFiles/Project.dir/Simulation/simulationImporter.cpp.o" \
"CMakeFiles/Project.dir/Simulation/autoSim.cpp.o" \
"CMakeFiles/Project.dir/Simulation/fileCompare.cpp.o" \
"CMakeFiles/Project.dir/Simulation/Vaccine.cpp.o"

# External object files for target Project
Project_EXTERNAL_OBJECTS =

Project: CMakeFiles/Project.dir/main.cpp.o
Project: CMakeFiles/Project.dir/XmlParser/tinystr.cpp.o
Project: CMakeFiles/Project.dir/XmlParser/tinyxml.cpp.o
Project: CMakeFiles/Project.dir/XmlParser/tinyxmlerror.cpp.o
Project: CMakeFiles/Project.dir/XmlParser/tinyxmlparser.cpp.o
Project: CMakeFiles/Project.dir/Simulation/Hub.cpp.o
Project: CMakeFiles/Project.dir/Simulation/Centrum.cpp.o
Project: CMakeFiles/Project.dir/Simulation/simulation.cpp.o
Project: CMakeFiles/Project.dir/Simulation/simulationImporter.cpp.o
Project: CMakeFiles/Project.dir/Simulation/autoSim.cpp.o
Project: CMakeFiles/Project.dir/Simulation/fileCompare.cpp.o
Project: CMakeFiles/Project.dir/Simulation/Vaccine.cpp.o
Project: CMakeFiles/Project.dir/build.make
Project: CMakeFiles/Project.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/frederic/Documents/Informatica/Sem2/PSE/Project/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Linking CXX executable Project"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Project.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Project.dir/build: Project

.PHONY : CMakeFiles/Project.dir/build

CMakeFiles/Project.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Project.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Project.dir/clean

CMakeFiles/Project.dir/depend:
	cd /Users/frederic/Documents/Informatica/Sem2/PSE/Project/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/frederic/Documents/Informatica/Sem2/PSE/Project /Users/frederic/Documents/Informatica/Sem2/PSE/Project /Users/frederic/Documents/Informatica/Sem2/PSE/Project/cmake-build-debug /Users/frederic/Documents/Informatica/Sem2/PSE/Project/cmake-build-debug /Users/frederic/Documents/Informatica/Sem2/PSE/Project/cmake-build-debug/CMakeFiles/Project.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Project.dir/depend

