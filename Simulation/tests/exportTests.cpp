/**
 * \n University of Antwerp - BA1 Informatica - Project Software Engineering 2021
 * \n Tests voor simulation exports
 *
 * @authors Frederic & Sander Marinus
 * @date    15/3/2021
 * @version 2.0
 */

#include <gtest/gtest.h>

#include <fstream>

#include "../fileCompare.h"

#include "../simulation.h"
#include "../Centrum.h"
#include "../Hub.h"
#include "../graphicExport.h"

class exporterTests : public ::testing::Test {
protected:

    virtual void SetUp() {
        // Set up for export
        c1 = new Centrum("Centrum 1", "Adres 1", 500, 200);
        c2 = new Centrum("Centrum 2", "Adres 2", 1000, 300);
        map<string, Centrum*> cMap;
        cMap.insert(pair<string, Centrum*>("Centrum 1", c1));
        cMap.insert(pair<string, Centrum*>("Centrum 2", c2));

        vac = new Vaccine;
        vector<Vaccine*> vVec;
        vVec.push_back(vac);

        h = new Hub(vVec, cMap);
        h->setVoorraad(vac, 1000);

        vector<Hub*> hubs;
        hubs.push_back(h);
        sim_.setHubs(hubs);

        vector<Centrum*> cVect;
        cVect.push_back(c1);
        cVect.push_back(c2);
        sim_.setCentra(cVect);
    }

    virtual void TearDown() {
    }

    // Variables to use in the tests
    simulation sim_;
    Centrum* c1;
    Centrum* c2;
    Hub* h;
    Vaccine* vac;
};

TEST_F(exporterTests, simpleOutSingleHub) {
    // Cast to string to compare
    // https://stackoverflow.com/questions/3513173/converting-ostream-into-standard-string

    ofstream oFile;
    oFile.open("../testOutput/export/singleHub1.txt");
    sim_.exportSim(oFile);
    oFile.close();
    EXPECT_TRUE(FileCompare("../testOutput/export/singleHub1.txt", "../expectedData/export/singleHub1.txt"));

    oFile.open("../testOutput/export/singleHub2.txt");
    h->setVoorraad(vac, 600);
    c2->setVoorraad(vac, 100);
    c2->setGevaccineerd(300);
    sim_.exportSim(oFile);
    oFile.close();
    EXPECT_TRUE(FileCompare("../testOutput/export/singleHub2.txt", "../expectedData/export/singleHub2.txt"));
}

TEST_F(exporterTests, simpleOutMultipleHubs) {
    Hub* nHub = new Hub();
    Vaccine* vaccine = new Vaccine();
    nHub->addCentrum(c1);
    nHub->addVaccine(vaccine);
    nHub->setVoorraad(vaccine, 100);

    vector<Hub*> hubs;
    hubs.push_back(h);
    hubs.push_back(nHub);
    sim_.setHubs(hubs);

    ofstream oFile;
    oFile.open("../testOutput/export/multipleHub.txt");
    sim_.exportSim(oFile);
    oFile.close();
    EXPECT_TRUE(FileCompare("../testOutput/export/multipleHub.txt", "../expectedData/export/multipleHub.txt"));
}

TEST_F(exporterTests, simpleGraphic) {
    ofstream oFile;
    oFile.open("../testOutput/export/simpleGraphic1.txt");

    sim_.graphicImpression(oFile);
    oFile.close();
    EXPECT_TRUE(FileCompare("../testOutput/export/simpleGraphic1.txt",
                            "../expectedData/export/simpleGraphic1.txt"));

    h->setVoorraad(vac, 600);
    c2->setVoorraad(vac, 100);
    c2->setGevaccineerd(300);

    oFile.open("../testOutput/export/simpleGraphic2.txt");
    sim_.graphicImpression(oFile);
    oFile.close();
    EXPECT_TRUE(FileCompare("../testOutput/export/simpleGraphic2.txt",
                            "../expectedData/export/simpleGraphic2.txt"));
}

TEST_F(exporterTests, statExport) {
    ofstream oFile;
    oFile.open("../testOutput/export/stats.txt");

    sim_.addDelivery("vaccine", 800);
    c2->verhoogEerste(400);
    c2->setGevaccineerd(100);
    c1->verhoogEerste(150);
    c1->setGevaccineerd(150);
    sim_.stats(oFile);

    EXPECT_TRUE(FileCompare("../testOutput/export/stats.txt", "../expectedData/export/stats.txt"));
}

TEST_F(exporterTests, gradientCalc) {
    vector<double> result = graphicExport::calculateGradient(100, 0);
    EXPECT_EQ(1.0, result[0]);
    EXPECT_EQ(0.0, result[1]);
    EXPECT_EQ(0.0, result[2]);

    result = graphicExport::calculateGradient(100, 50);
    EXPECT_EQ(1.0, result[0]);
    EXPECT_EQ(1.0, result[1]);
    EXPECT_EQ(0.0, result[2]);

    result = graphicExport::calculateGradient(100, 100);
    EXPECT_EQ(0.0, result[0]);
    EXPECT_EQ(1.0, result[1]);
    EXPECT_EQ(0.0, result[2]);

    result = graphicExport::calculateGradient(100, 25);
    EXPECT_EQ(1.0, result[0]);
    EXPECT_EQ(0.5, result[1]);
    EXPECT_EQ(0.0, result[2]);

    result = graphicExport::calculateGradient(100, 75);
    EXPECT_EQ(0.5, result[0]);
    EXPECT_EQ(1.0, result[1]);
    EXPECT_EQ(0.0, result[2]);
}

TEST_F(exporterTests, iniVectorSegment) {
    ofstream oFile;
    oFile.open("../testOutput/export/vectorSegment.txt");
    graphicExport::iniAdd3dVectorSegment("ambient", 0, 1, 1, oFile);
    oFile.close();
    EXPECT_TRUE(FileCompare("../testOutput/export/vectorSegment.txt",
                            "../expectedData/export/vectorSegment.txt"));
}

TEST_F(exporterTests, iniHub) {
    ofstream oFile;
    oFile.open("../testOutput/export/hub.txt");
    graphicExport::iniAddHub(0, oFile);
    oFile.close();

    EXPECT_TRUE(FileCompare("../testOutput/export/hub.txt", "../expectedData/export/hub.txt"));
}

TEST_F(exporterTests, iniHubStock) {
    ofstream oFile;
    oFile.open("../testOutput/export/hubStock.txt");
    int figNum = graphicExport::iniAddHubStock(h, 0, 400, 1, oFile);
    oFile.close();

    EXPECT_EQ(3, figNum);
    EXPECT_TRUE(FileCompare("../testOutput/export/hubStock.txt", "../expectedData/export/hubStock.txt"));
}

TEST_F(exporterTests, iniCenter) {
    ofstream oFile;
    oFile.open("../testOutput/export/center1.txt");
    graphicExport::iniAddCenter(c1, 1, 0, 3, oFile);
    oFile.close();

    EXPECT_TRUE(FileCompare("../testOutput/export/center1.txt", "../expectedData/export/center1.txt"));

    c1->setVoorraad(vac, 400);
    c1->setGevaccineerd(250);
    oFile.open("../testOutput/export/center2.txt");
    graphicExport::iniAddCenter(c1, 0, 0, 3, oFile);
    oFile.close();

    EXPECT_TRUE(FileCompare("../testOutput/export/center2.txt", "../expectedData/export/center2.txt"));
}

TEST_F(exporterTests, iniTransport) {
    ofstream oFile;
    oFile.open("../testOutput/export/transport.txt");
    graphicExport::iniAddTransports(3, 1, 1, 3, 2, oFile);
    oFile.close();

    EXPECT_TRUE(FileCompare("../testOutput/export/transport.txt", "../expectedData/export/transport.txt"));
}

TEST_F(exporterTests, iniGeneral) {
    ofstream oFile;
    oFile.open("../testOutput/export/general.txt");
    graphicExport::iniGeneral(10, 5, oFile);
    oFile.close();

    EXPECT_TRUE(FileCompare("../testOutput/export/general.txt", "../expectedData/export/general.txt"));
}

TEST_F(exporterTests, iniFull) {
    map<Centrum*, int> transports;
    transports[c1] = 2;
    transports[c2] = 0;
    c1->setVoorraad(vac, 200);
    graphicExport::createIni(h, 1, 400, transports, 0, "../testOutput/export");

    EXPECT_TRUE(FileCompare("../testOutput/export/hub01_dag0000.ini", "../expectedData/export/fullIni.ini"));
}
