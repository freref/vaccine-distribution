/**
 * \n University of Antwerp - BA1 Informatica - Project Software Engineering 2021
 * \n Tests voor simulation exporter
 *
 * @authors Frederic Hamelink & Sander Marinus
 * @date    15/3/2021
 * @version 1.0
 */

#include <gtest/gtest.h>

#include "../simulation.h"
#include "../Centrum.h"
#include "../Hub.h"

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
        vac->setVoorraad(1000);
        vector<Vaccine*> vVec;
        vVec.push_back(vac);

        h = new Hub(vVec, cMap);
        sim_.setHub(h);
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

TEST_F(exporterTests, simpleOutHappyDay) {
    // Cast to string to compare
    // https://stackoverflow.com/questions/3513173/converting-ostream-into-standard-string
    ostringstream strStream;
    sim_.exportSim(strStream);
    string actual = strStream.str();
    string expected = "Hub (1000)\n"
                      "\t-> Centrum 1 (0 vaccins)\n"
                      "\t-> Centrum 2 (0 vaccins)\n"
                      "\n"
                      "Centrum 1: 0 gevaccineerd, nog 500 inwoners niet gevaccineerd\n"
                      "Centrum 2: 0 gevaccineerd, nog 1000 inwoners niet gevaccineerd\n";
    EXPECT_EQ(expected, actual);

    strStream.str("");
    vac->setVoorraad(600);
    c2->setVoorraad(vac, 100);
    c2->setGevaccineerd(300);
    sim_.exportSim(strStream);
    string actual2 = strStream.str();
    expected = "Hub (600)\n"
               "\t-> Centrum 1 (0 vaccins)\n"
               "\t-> Centrum 2 (100 vaccins)\n"
               "\n"
               "Centrum 1: 0 gevaccineerd, nog 500 inwoners niet gevaccineerd\n"
               "Centrum 2: 300 gevaccineerd, nog 700 inwoners niet gevaccineerd\n";
    EXPECT_EQ(expected, actual2);
}

TEST_F(exporterTests, simpleGraphicHappyDay) {
    ostringstream strStream;
    sim_.graphicImpression(strStream);
    string actual = strStream.str();

    string expected = "Centrum 1:\n"
                      "\t- vaccins\t\t[                    ] 0%\n"
                      "\t- gevaccineerd\t[                    ] 0%\n"
                      "Centrum 2:\n"
                      "\t- vaccins\t\t[                    ] 0%\n"
                      "\t- gevaccineerd\t[                    ] 0%\n";
    EXPECT_EQ(expected, actual);

    strStream.str("");
    vac->setVoorraad(600);
    c2->setVoorraad(vac, 100);
    c2->setGevaccineerd(300);
    sim_.graphicImpression(strStream);
    actual = strStream.str();

    expected = "Centrum 1:\n"
                      "\t- vaccins\t\t[                    ] 0%\n"
                      "\t- gevaccineerd\t[                    ] 0%\n"
                      "Centrum 2:\n"
                      "\t- vaccins\t\t[===                 ] 16%\n"
                      "\t- gevaccineerd\t[======              ] 30%\n";
    EXPECT_EQ(expected, actual);
}