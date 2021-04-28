cmake_minimum_required(VERSION 3.17)
project(Project)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-Wall -Werror")
set(CMAKE_EXE_LINKER_FLAGS -pthread)

# Set include dir
include_directories(gtest/include)
# Set Library dir
link_directories(gtest/lib)

# Set source files
set(SOURCE_FILES
        XmlParser/tinystr.cpp
        XmlParser/tinyxml.cpp
        XmlParser/tinyxmlerror.cpp
        XmlParser/tinyxmlparser.cpp
        Simulation/Hub.cpp
        Simulation/Centrum.cpp
        Simulation/simulation.cpp
        Simulation/simulationImporter.cpp
        Simulation/autoSim.cpp
        Simulation/Vaccine.cpp Simulation/Vaccine.h
        Simulation/algemeen.cpp)

set(DEBUG_FILES
        Simulation/tests/autoSimTests.cpp
        Simulation/tests/centrumTests.cpp
        Simulation/tests/domainTests.cpp
        Simulation/tests/exportTests.cpp
        Simulation/tests/importTests.cpp
        Simulation/fileCompare.cpp)

# Create executables
add_executable(Project main.cpp ${SOURCE_FILES})

add_executable(sim_debug tests_main.cpp ${SOURCE_FILES} ${DEBUG_FILES})

# Link library
target_link_libraries(sim_debug gtest)