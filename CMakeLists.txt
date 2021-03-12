cmake_minimum_required(VERSION 3.17)
project(Project)

set(CMAKE_CXX_STANDARD 98)

set(SOURCE_FILES main.cpp
        XmlParser/tinystr.cpp XmlParser/tinystr.h
        XmlParser/tinyxml.cpp XmlParser/tinyxml.h
        XmlParser/tinyxmlerror.cpp
        XmlParser/tinyxmlparser.cpp
        Simulation/Hub.cpp Simulation/Hub.h
        Simulation/Centrum.cpp Simulation/Centrum.h
        Simulation/simulation.cpp Simulation/simulation.h
        Simulation/simulationImporter.cpp Simulation/simulationImporter.h Simulation/simulationExporter.cpp Simulation/simulationExporter.h Simulation/autoSim.cpp Simulation/autoSim.h)

add_executable(Project ${SOURCE_FILES})