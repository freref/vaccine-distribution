/**
 * University of Antwerp - BA1 Informatica - Project Software Engineering 2021
 * Tests voor simulation importer
 *
 * @authors Frederic Hamelink & Sander Marinus
 * @date    16/3/2021
 * @version 1.0
 */

#include <gtest/gtest.h>

#include "../Simulation/simulation.h"
#include "../Simulation/simulationImporter.h"

class importTests : public ::testing::Test {
protected:

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }

    // Variables to use in the tests
    simulation sim_;
};


TEST_F(importTests, happyDayImport) {
    simulationImporter::importFile("data1.xml", sim_);
}