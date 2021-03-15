cmake_minimum_required(VERSION 3.17)
project(Project)

set(CMAKE_CXX_STANDARD 98)
#set(CMAKE_CXX_FLAGS "-Wall -Werror -O2")
set(CMAKE_EXE_LINKER_FLAGS -pthread)

# Set include dir
include_directories(gtest/include)
# Set Library dir
link_directories(gtest/lib)

# Set source files
set(SOURCE_FILES main.cpp
        XmlParser/tinystr.cpp
        XmlParser/tinyxml.cpp
        XmlParser/tinyxmlerror.cpp
        XmlParser/tinyxmlparser.cpp
        Simulation/Hub.cpp
        Simulation/Centrum.cpp
        Simulation/simulation.cpp
        Simulation/simulationImporter.cpp
        Simulation/simulationExporter.cpp
        Simulation/autoSim.cpp)

set(DEBUG_FILES tests_main.cpp
        XmlParser/tinystr.cpp
        XmlParser/tinyxml.cpp
        XmlParser/tinyxmlerror.cpp
        XmlParser/tinyxmlparser.cpp
        Simulation/Hub.cpp
        Simulation/Centrum.cpp
        Simulation/simulation.cpp
        Simulation/simulationImporter.cpp
        Simulation/simulationExporter.cpp
        Simulation/autoSim.cpp
        tests/autoSimTests.cpp
        tests/domainTests.cpp)

# Create executables
add_executable(Project ${SOURCE_FILES})

add_executable(sim_debug ${DEBUG_FILES})

# Link library
target_link_libraries(sim_debug gtest)