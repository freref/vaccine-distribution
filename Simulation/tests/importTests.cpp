/**
 * \n University of Antwerp - BA1 Informatica - Project Software Engineering 2021
 * \n Tests voor simulation importer
 *
 * @authors Frederic Hamelink & Sander Marinus
 * @date    16/3/2021
 * @version 1.0
 */

#include <gtest/gtest.h>
#include <iostream>
#include <fstream>

#include "../simulation.h"
#include "../simulationImporter.h"
#include "../Hub.h"
#include "../Centrum.h"
#include "../fileCompare.h"

class importTests : public ::testing::Test {
protected:

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }

    // Variables to use in the tests
    simulation sim_;
};

TEST_F(importTests, testFileFunctions) {
    // Test empty check function
    EXPECT_TRUE(FileIsEmpty("emptyFile.xml"));
    EXPECT_FALSE(FileIsEmpty("data1.xml"));
    // Test compare function
    EXPECT_TRUE(FileCompare("data1.xml", "data1.xml"));
    EXPECT_FALSE(FileCompare("data1.xml", "badData1.xml"));
}

TEST_F(importTests, happyDayImport) {
    simulationImporter::importFile("data1.xml", sim_, cerr);
    EXPECT_EQ(93000, sim_.getHub()->getLevering());
    EXPECT_EQ(93000, sim_.getHub()->getVoorraad());
    EXPECT_EQ(6, sim_.getHub()->getInterval());
    EXPECT_EQ(2000, sim_.getHub()->getTransport());
    EXPECT_EQ((long unsigned int) (4), sim_.getHub()->getCentra().size());
    EXPECT_EQ((long unsigned int) (4), sim_.getCentra().size());
}

TEST_F(importTests, empty_nonexistingFile) {
    ostringstream strStream;
    EXPECT_EQ(1, simulationImporter::importFile("nonexistingFile.xml", sim_, strStream));
    string expected = "Error reading nonexistingFile.xml: Failed to open file\n";
    string actual = strStream.str();
    EXPECT_EQ(expected, actual);
    strStream.str("");
    EXPECT_EQ(1, simulationImporter::importFile("emptyFile.xml", sim_, strStream));
    expected = "Error reading emptyFile.xml: Error document empty.\n";
    actual = strStream.str();
    EXPECT_EQ(expected, actual);
}

TEST_F(importTests, badFiles) {
    string baseIn = "badData";
    for (int i = 1; i <= 16; ++i) {
        ofstream outFile;
        ostringstream convert;
        // Iteratie int naar string
        convert << i;
        string compare = "compare.txt";
        // Open met trunc om leeg te maken
        outFile.open(compare.c_str(), std::ofstream::out | std::ofstream::trunc);
        // File namen opstellen
        string file = baseIn + convert.str() + ".xml";
        string expected = "../expectedData/" + baseIn + convert.str() + ".txt";
        // Tests uitvoeren
        EXPECT_NE(0, simulationImporter::importFile(file, sim_, outFile));
        EXPECT_TRUE(FileCompare(compare, expected));
    }
}

TEST_F(importTests, partialFiles) {
    string baseIn = "partialData";
    for (int i = 1; i <= 4; ++i) {
        ofstream outFile;
        ostringstream convert;
        // Iteratie int naar string
        convert << i;
        string compare = "compare.txt";
        // Open met trunc om leeg te maken
        outFile.open(compare.c_str(), std::ofstream::out | std::ofstream::trunc);
        // File namen opstellen
        string file = baseIn + convert.str() + ".xml";
        string expected = "../expectedData/" + baseIn + convert.str() + ".txt";
        // Tests uitvoeren
        EXPECT_EQ(0, simulationImporter::importFile(file, sim_, outFile));
        EXPECT_TRUE(FileCompare(compare, expected));
    }
}

TEST_F(importTests, badInt) {
    string baseIn = "throw";
    for (int i = 1; i <= 4; ++i) {
        ostringstream strStream;
        ostringstream convert;
        convert << i;
        string file = baseIn + convert.str() + ".xml";
        EXPECT_ANY_THROW(simulationImporter::importFile(file, sim_, strStream));
    }
}