/**
 * University of Antwerp - BA1 Informatica - Project Software Engineering 2021
 * Tests voor simulation exporter
 *
 * @authors Frederic Hamelink & Sander Marinus
 * @date    15/3/2021
 * @version 1.0
 */

#include <gtest/gtest.h>

#include "../Simulation/simulation.h"
#include "../Simulation/Centrum.h"
#include "../Simulation/Hub.h"
#include "../Simulation/simulationExporter.h"

class exporterTests : public ::testing::Test {
protected:

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }

    // Variables to use in the tests
    simulation sim_;
};

TEST_F(exporterTests, outputHappyDay) {
    // Set up for export
    Centrum* c1 = new Centrum("Centrum 1", "Adres 1", 500, 200);
    Centrum* c2 = new Centrum("Centrum 2", "Adres 2", 1000, 300);
    map<string, Centrum*> cMap;
    cMap.insert(pair<string, Centrum*>("Centrum 1", c1));
    cMap.insert(pair<string, Centrum*>("Centrum 2", c2));
    Hub* h = new Hub(1000, 3, 200, cMap);
    sim_.setHub(h);
    vector<Centrum*> cVect;
    cVect.push_back(c1);
    cVect.push_back(c2);
    sim_.setCentra(cVect);

    // Cast to string to compare
    // https://stackoverflow.com/questions/3513173/converting-ostream-into-standard-string
    ostringstream strStream;
    simulationExporter::exportSim(strStream, sim_);
    string actual = strStream.str();
    string expected = "Hub (1000)\n"
                      "\t-> Centrum 1 (0 vaccins)\n"
                      "\t-> Centrum 2 (0 vaccins)\n"
                      "\n"
                      "Centrum 1: 0 gevaccineerd, nog 500 inwoners niet gevaccineerd\n"
                      "Centrum 2: 0 gevaccineerd, nog 1000 inwoners niet gevaccineerd\n";
    EXPECT_EQ(expected, actual);

    strStream.str("");
    c2->setVaccins(100);
    c2->setGevaccineerd(300);
    simulationExporter::exportSim(strStream, sim_);
    string actual2 = strStream.str();
    expected = "Hub (1000)\n"
               "\t-> Centrum 1 (0 vaccins)\n"
               "\t-> Centrum 2 (100 vaccins)\n"
               "\n"
               "Centrum 1: 0 gevaccineerd, nog 500 inwoners niet gevaccineerd\n"
               "Centrum 2: 300 gevaccineerd, nog 700 inwoners niet gevaccineerd\n";
    EXPECT_EQ(expected, actual2);
}