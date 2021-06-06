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
        outBase = "../testOutput/import/";
        compBase = "../expectedData/import/";
    }

    virtual void TearDown() {
        sim_.clear();
    }

    // Variables to use in the tests
    simulation sim_;
    string outBase;
    string compBase;
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
    ostringstream strStream;
    simulationImporter::importFile("data1.xml", sim_, strStream);
    EXPECT_TRUE(strStream.str().empty());

    EXPECT_EQ((long unsigned int) (1), sim_.getHubs().size());
    EXPECT_EQ((long unsigned int) (4), sim_.getHubs()[0]->getCentra().size());
    EXPECT_EQ((long unsigned int) (4), sim_.getCentra().size());
    EXPECT_EQ((unsigned int) (3), sim_.getHubs()[0]->getVaccins().size());

    EXPECT_EQ(0, sim_.getHubs()[0]->getTotaleVoorraad());
    Vaccine* vac = sim_.getHubs()[0]->getVaccins()[0];
    EXPECT_EQ(25000, vac->getLevering());
    EXPECT_EQ(500, vac->getTransport());
    EXPECT_EQ(-70, vac->getTemperatuur());
}

TEST_F(importTests, correctData) {
    stringstream conv;
    ofstream oFile;
    for (int i = 1; i <= 4; ++i) {
        conv.str("");
        conv << i;
        string inFile = "data" + conv.str() + ".xml";
        string outFile = outBase + "outData" + conv.str() + ".txt";

        oFile.open(outFile.c_str());
        simulationImporter::importFile(inFile, sim_, oFile);
        oFile.close();

        EXPECT_TRUE(FileIsEmpty(outFile));
    }
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
    ofstream outFile;
    for (int i = 1; i <= 15; ++i) {
        cout << i << endl;

        ostringstream convert;
        // Iteratie int to string
        convert << i;
        // Create filenames
        string compare = outBase + "outBadData" + convert.str() + ".txt"; // Output file
        string file = baseIn + convert.str() + ".xml"; // Import file
        string expected = compBase + baseIn + convert.str() + ".txt"; // Expected output

        outFile.open(compare.c_str());
        // Tests uitvoeren
        EXPECT_NE(0, simulationImporter::importFile(file, sim_, outFile));
        outFile.close();
        EXPECT_TRUE(FileCompare(compare, expected));
    }
}

//TEST_F(importTests, partialFiles) {
//    string baseIn = "partialData";
//    ofstream outFile;
//    for (int i = 1; i <= 8; ++i) {
//        // cout << i << endl;
//
//        ostringstream convert;
//        // Iteratie int to string
//        convert << i;
//        // Create filenames
//        string compare = outBase + "outPartialData" + convert.str() + ".txt"; // Output file
//        string file = baseIn + convert.str() + ".xml"; // Import file
//        string expected = compBase + baseIn + convert.str() + ".txt"; // Expected output
//
//        outFile.open(compare.c_str());
//
//        // Tests uitvoeren
//        EXPECT_EQ(0, simulationImporter::importFile(file, sim_, outFile));
//        outFile.close();
//        EXPECT_TRUE(FileCompare(compare, expected));
//    }
//}
//
//TEST_F(importTests, badInt) {
//    string baseIn = "throw";
//    for (int i = 1; i <= 3; ++i) {
//        // cout << i << endl;
//
//        ostringstream strStream;
//        ostringstream convert;
//        convert << i;
//        string file = baseIn + convert.str() + ".xml";
//        EXPECT_ANY_THROW(simulationImporter::importFile(file, sim_, strStream));
//    }
//}
//
//TEST_F(importTests, death) {
//    string baseIn = "death";
//    for (int i = 1; i <= 1; ++i) {
//        // cout << i << endl;
//
//        ostringstream strStream;
//        ostringstream convert;
//        convert << i;
//        string file = baseIn + convert.str() + ".xml";
//        EXPECT_DEATH(simulationImporter::importFile(file, sim_, strStream), "Assertion.*");
//    }
//}