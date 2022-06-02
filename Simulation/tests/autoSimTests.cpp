/**
 * \n University of Antwerp - BA1 Informatica - Project Software Engineering 2021
 * \n Tests the automation of the simulation
 *
 * @authors Frederic & Sander Marinus
 * @date    15/3/2021
 * @version 2.0
 */

#include <gtest/gtest.h>
#include <fstream>
#include <iomanip>

#include "../fileCompare.h"

#include "../autoSim.h"
#include "../simulation.h"
#include "../Hub.h"
#include "../Centrum.h"
#include "../Vaccine.h"

// Classes to create output stream without output
// https://stackoverflow.com/questions/11826554/standard-no-output-stream
class NullBuffer : public streambuf {
public:
    int overflow(int c) { return c; }
};

class NullStream : public ostream {
public:
    NullStream() : ostream(&m_sb) {}
private:
    NullBuffer m_sb;
};


// Test environment
// Resembles a set of tests
class autoSimTests : public ::testing::Test {
protected:
    friend class simulation;

    // Function SetUp called before every test
    // Use to declare the variables
    virtual void SetUp() {
        strStrm.str("");

        c_ = new Centrum("Centrum", "Straat 1", 500, 100);
        map<string, Centrum*> cMap;
        cMap.insert(pair<string, Centrum*>("Centrum", c_));

        v_ = new Vaccine("vac", 1000, 2, 45, 1, 2);
        vector<Vaccine*> vacVec;
        vacVec.push_back(v_);

        h_ = new Hub(vacVec, cMap);
        h_->setVoorraad(v_, 1000);
        vector<Hub*> hubs;
        hubs.push_back(h_);

        sim_.setHubs(hubs);
        sim_.addCentrum(c_);
    }

    // Variables to use in the tests
    NullStream null_stream;
    simulation sim_;
    Vaccine* v_;
    Centrum* c_;
    Hub* h_;
    ostringstream strStrm;
};

// The actual tests

TEST_F(autoSimTests, setupCheck) {
    EXPECT_EQ(1000, h_->getTotaleVoorraad());
    EXPECT_EQ(45, v_->getTransport());
    EXPECT_EQ(0, c_->getVaccins());
    EXPECT_EQ(3, c_->berekenEerstePrikLadingen(h_, v_, 0, 1000));
    EXPECT_EQ(0, c_->berekenTweedePrikLadingen(h_, v_, 0));
    EXPECT_TRUE(strStrm.str().empty());
}

TEST_F(autoSimTests, centrumTransport) {
    autoSim::simulateTransport(h_, c_, v_, 45, strStrm);
    EXPECT_EQ(955, h_->getTotaleVoorraad());
    EXPECT_EQ(45, c_->getVaccins());
    EXPECT_EQ(2, c_->berekenEerstePrikLadingen(h_, v_, 0, 1000));
    EXPECT_EQ("Er werden 1 ladingen vac (45 vaccins) getransporteerd naar Centrum.\n", strStrm.str());
}

TEST_F(autoSimTests, firstInjTransport) {
    map<Centrum*, int> transports;
    // Initial transport
    map<string, Centrum*> cMap = h_->getCentra();
    vector<Vaccine*> vacVec = h_->getVaccins();
    autoSim::simulateEerstePrikTransport(h_, cMap, vacVec, transports, strStrm, 0);
    EXPECT_EQ("Er werden 3 ladingen vac (135 vaccins) getransporteerd naar Centrum.\n", strStrm.str());
    EXPECT_EQ(865, h_->getTotaleVoorraad());
    EXPECT_EQ(135, c_->getVaccins());
    EXPECT_EQ(0, c_->berekenEerstePrikLadingen(h_, v_, 0, 1000));
    EXPECT_EQ(0, c_->berekenTweedePrikLadingen(h_, v_, 0));
    EXPECT_EQ(3, transports[c_]);

    // New transport, no changes to stocks
    strStrm.str("");
    autoSim::simulateEerstePrikTransport(h_, cMap, vacVec, transports, strStrm, 1);
    cout << strStrm.str() << endl;
    EXPECT_EQ("", strStrm.str());
    EXPECT_EQ(865, h_->getTotaleVoorraad());
    EXPECT_EQ(135, c_->getVaccins());
    EXPECT_EQ(0, c_->berekenEerstePrikLadingen(h_, v_, 0, 1000));
    EXPECT_EQ(0, c_->berekenTweedePrikLadingen(h_, v_, 0));
    EXPECT_EQ(3, transports[c_]);
}

TEST_F(autoSimTests, secondInjTransport) {
    map<Centrum*, int> transports;
    // Initial transport
    c_->zetVaccinatie(0, v_, 100);
    c_->verhoogEerste(100);
    map<string, Centrum*> cMap = h_->getCentra();
    vector<Vaccine*> vacVec = h_->getVaccins();
    autoSim::simulateTweedePrikTransport(h_, cMap, vacVec, transports, strStrm, 1);
    EXPECT_EQ("Er werden 3 ladingen vac (135 vaccins) getransporteerd naar Centrum.\n", strStrm.str());
    EXPECT_EQ(135, c_->getVaccins());
    EXPECT_EQ(100, c_->getEerste());
    EXPECT_EQ(0, c_->getGevaccineerd());
    EXPECT_EQ(3, transports[c_]);

    // Second transport, no changes to stock/day
    strStrm.str("");
    autoSim::simulateTweedePrikTransport(h_, cMap, vacVec, transports, strStrm, 1);
    EXPECT_EQ("", strStrm.str());
    EXPECT_EQ(135, c_->getVaccins());
    EXPECT_EQ(100, c_->getEerste());
    EXPECT_EQ(0, c_->getGevaccineerd());
    EXPECT_EQ(3, transports[c_]);
}

TEST_F(autoSimTests, negativeTempTransport) {
    map<Centrum*, int> transports;
    // Check transport for first injection of vaccine stored in negative temperature
    v_->setTemperatuur(-5);
    map<string, Centrum*> cMap = h_->getCentra();
    vector<Vaccine*> vacVec = h_->getVaccins();
    autoSim::simulateEerstePrikTransport(h_, cMap, vacVec, transports, strStrm, 0);
    EXPECT_EQ("Er werden 2 ladingen vac (90 vaccins) getransporteerd naar Centrum.\n", strStrm.str());
    EXPECT_EQ(910, h_->getTotaleVoorraad());
    EXPECT_EQ(90, c_->getVaccins());
    EXPECT_EQ(0, c_->berekenEerstePrikLadingen(h_, v_, 0, 1000));
    EXPECT_EQ(0, c_->berekenTweedePrikLadingen(h_, v_, 0));
    EXPECT_EQ(2, transports[c_]);

    // Add new vaccine
    Vaccine* vac = new Vaccine("vac2", 1000, 2, 20, 1, -2);
    h_->addVaccine(vac);
    h_->setVoorraad(vac, 90);
    vacVec = h_->getVaccins();
    c_->zetVaccinatie(0, vac, 100);
    c_->verhoogEerste(100);

    // Check transport for second injections of vaccine stored in negative temperature
    // Not enough room to make sure single load is injected that day
    strStrm.str("");
    autoSim::simulateTweedePrikTransport(h_, cMap, vacVec, transports, strStrm, 1);
    EXPECT_EQ("Er werden 1 ladingen vac2 (20 vaccins) getransporteerd naar Centrum.\n", strStrm.str());
    EXPECT_EQ(980, h_->getTotaleVoorraad());
    EXPECT_EQ(110, c_->getVaccins());
    EXPECT_EQ(0, c_->berekenEerstePrikLadingen(h_, v_, 0, 1000));
    EXPECT_EQ(0, c_->berekenTweedePrikLadingen(h_, v_, 0));
    EXPECT_EQ(0, c_->berekenEerstePrikLadingen(h_, vac, 0, 1000));
    EXPECT_EQ(0, c_->berekenTweedePrikLadingen(h_, vac, 0));
    EXPECT_EQ(3, transports[c_]);
}

TEST_F(autoSimTests, correctInjections) {
    c_->setVoorraad(v_, 135);
    c_->zetVaccinatie(0, v_, 50);
    c_->verhoogEerste(50);
    autoSim::simulateVaccinatie(c_, 1, strStrm);
    EXPECT_FALSE(strStrm.str().empty());
    EXPECT_EQ(100, c_->getEerste());
    EXPECT_EQ(50, c_->getGevaccineerd());
    EXPECT_EQ(35, c_->getVaccins());

    strStrm.str("");
    autoSim::simulateVaccinatie(c_, 2, strStrm);
    EXPECT_FALSE(strStrm.str().empty());
    EXPECT_EQ(100, c_->getEerste());
    EXPECT_EQ(85, c_->getGevaccineerd());
    EXPECT_EQ(0, c_->getVaccins());
}

TEST_F(autoSimTests, noRenewalTest) {
    v_->setHernieuwing(0);
    c_->setVoorraad(v_, 135);
    autoSim::simulateVaccinatie(c_, 1, strStrm);
    EXPECT_FALSE(strStrm.str().empty());
    EXPECT_EQ(100, c_->getEerste());
    EXPECT_EQ(100, c_->getGevaccineerd());
    EXPECT_EQ(35, c_->getVaccins());

    strStrm.str("");
    autoSim::simulateVaccinatie(c_, 2, strStrm);
    EXPECT_FALSE(strStrm.str().empty());
    EXPECT_EQ(135, c_->getEerste());
    EXPECT_EQ(135, c_->getGevaccineerd());
    EXPECT_EQ(0, c_->getVaccins());
}

TEST_F(autoSimTests, hubRestock) {
    vector<Vaccine*> vacVec = h_->getVaccins();
    autoSim::simulateHubDelivery(h_, sim_, vacVec, 3);
    EXPECT_EQ(2000, h_->getTotaleVoorraad());
    EXPECT_EQ(1000, sim_.getDeliveries()["vac"]);
}

TEST_F(autoSimTests, autoSimulation) {
    h_->setVoorraad(v_, 0);
    ofstream oFile;
    oFile.open("../testOutput/autoSim/out.txt");
    autoSim::simulate(sim_, 3, "../testOutput/autoSim", 10000, true, oFile);
    EXPECT_TRUE(FileCompare("../testOutput/autoSim/out.txt", "../expectedData/autoSim1.txt"));
    EXPECT_EQ(1000, sim_.getDeliveries()["vac"]);
    EXPECT_EQ(685, h_->getTotaleVoorraad());
    EXPECT_EQ(15, c_->getVaccins());
    EXPECT_EQ(100, c_->getGevaccineerd());
    EXPECT_EQ(200, c_->getEerste());

    autoSim::simulate(sim_, 10, "../testOutput/autoSim"
                      , 10000, false, null_stream);
    EXPECT_EQ(500, c_->getGevaccineerd());
    EXPECT_EQ(500, c_->getEerste());
    EXPECT_EQ(35, c_->getVaccins());
    EXPECT_EQ(2965, h_->getTotaleVoorraad());
    EXPECT_EQ(4000, sim_.getDeliveries()["vac"]);

    for (int i = 1; i <= 3; i++) {
        stringstream conv;
        conv << setw(4) << setfill('0') << i;
        string path = "../testOutput/autoSim/hub00_dag" + conv.str() + ".ini";
        EXPECT_FALSE(FileIsEmpty(path));
    }
    for (int i = 4; i <= 10; i++) {
        stringstream conv;
        conv << setw(4) << setfill('0') << i;
        string path = "../testOutput/autoSim/hub0_dag" + conv.str() + ".ini";
        ifstream iFile;
        iFile.open(path.c_str());
        EXPECT_FALSE(iFile.good());
    }
}
