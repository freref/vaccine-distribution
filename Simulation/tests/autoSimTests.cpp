/**
 * \n University of Antwerp - BA1 Informatica - Project Software Engineering 2021
 * \n Tests the automatic simulation
 *
 * @authors Frederic Hamelink & Sander Marinus
 * @date    15/3/2021
 * @version 1.0
 */

#include <gtest/gtest.h>

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
class simulationSimTests : public ::testing::Test {
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
        sim_.setHub(h_);
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

TEST_F(simulationSimTests, setupCheck) {
    EXPECT_EQ(1000, h_->accessorTotaleVoorraad());
    EXPECT_EQ(45, v_->getTransport());
    EXPECT_EQ(0, c_->getVaccins());
    EXPECT_EQ(3, c_->berekenEerstePrikLadingen(v_, 0, 1000));
    EXPECT_EQ(0, c_->berekenTweedePrikLadingen(v_, 0));
    EXPECT_TRUE(strStrm.str().empty());
}

TEST_F(simulationSimTests, // Parent test class
       centrumTransport) { // Name of the test
    autoSim::simulateTransport(c_, v_, 45, strStrm);
    EXPECT_EQ(955, h_->accessorTotaleVoorraad());
    EXPECT_EQ(45, c_->getVaccins());
    EXPECT_EQ(2, c_->berekenEerstePrikLadingen(v_, 0, 1000));
    EXPECT_FALSE(strStrm.str().empty());
}

TEST_F(simulationSimTests, firstInjTransport) {
    map<string, Centrum*> cMap = h_->getCentra();
    vector<Vaccine*> vacVec = h_->getVaccins();
    autoSim::simulateEerstePrikTransport(&cMap, &vacVec, strStrm, 0);
    EXPECT_FALSE(strStrm.str().empty());
    EXPECT_EQ(865, h_->accessorTotaleVoorraad());
    EXPECT_EQ(135, c_->getVaccins());
    EXPECT_EQ(0, c_->berekenEerstePrikLadingen(v_, 0, 1000));
    EXPECT_EQ(0, c_->berekenTweedePrikLadingen(v_, 0));

    strStrm.str("");
    autoSim::simulateEerstePrikTransport(&cMap, &vacVec, strStrm, 0);
    cout << strStrm.str() << endl;
    EXPECT_TRUE(strStrm.str().empty());
    EXPECT_EQ(865, h_->accessorTotaleVoorraad());
    EXPECT_EQ(135, c_->getVaccins());
    EXPECT_EQ(0, c_->berekenEerstePrikLadingen(v_, 0, 1000));
    EXPECT_EQ(0, c_->berekenTweedePrikLadingen(v_, 0));
}

TEST_F(simulationSimTests, secondInjTransport) {
    c_->zetVaccinatie(0, v_, 100);
    c_->verhoogEerste(100);
    map<string, Centrum*> cMap = h_->getCentra();
    vector<Vaccine*> vacVec = h_->getVaccins();
    autoSim::simulateTweedePrikTransport(&cMap, &vacVec, strStrm, 1);
    EXPECT_FALSE(strStrm.str().empty());
    EXPECT_EQ(135, c_->getVaccins());
    EXPECT_EQ(100, c_->getEerste());
    EXPECT_EQ(0, c_->getGevaccineerd());
}

TEST_F(simulationSimTests, negativeTempTransport) {
    v_->setTemperatuur(-5);
    map<string, Centrum*> cMap = h_->getCentra();
    vector<Vaccine*> vacVec = h_->getVaccins();
    autoSim::simulateEerstePrikTransport(&cMap, &vacVec, strStrm, 0);
    EXPECT_FALSE(strStrm.str().empty());
    EXPECT_EQ(910, h_->accessorTotaleVoorraad());
    EXPECT_EQ(90, c_->getVaccins());
    EXPECT_EQ(0, c_->berekenEerstePrikLadingen(v_, 0, 1000));
    EXPECT_EQ(0, c_->berekenTweedePrikLadingen(v_, 0));
}

TEST_F(simulationSimTests, correctInjections) {
    c_->setVoorraad(v_, 135);
    c_->zetVaccinatie(0, v_, 50);
    c_->verhoogEerste(50);
    autoSim::simulateVaccinatie(c_, strStrm, 1);
    EXPECT_FALSE(strStrm.str().empty());
    EXPECT_EQ(100, c_->getEerste());
    EXPECT_EQ(50, c_->getGevaccineerd());
    EXPECT_EQ(35, c_->getVaccins());

    strStrm.str("");
    autoSim::simulateVaccinatie(c_, strStrm, 2);
    EXPECT_FALSE(strStrm.str().empty());
    EXPECT_EQ(100, c_->getEerste());
    EXPECT_EQ(85, c_->getGevaccineerd());
    EXPECT_EQ(0, c_->getVaccins());
}

TEST_F(simulationSimTests, noRenewalTest) {
    v_->setHernieuwing(0);
    c_->setVoorraad(v_, 135);
    autoSim::simulateVaccinatie(c_, strStrm, 1);
    EXPECT_FALSE(strStrm.str().empty());
    EXPECT_EQ(100, c_->getEerste());
    EXPECT_EQ(100, c_->getGevaccineerd());
    EXPECT_EQ(35, c_->getVaccins());

    strStrm.str("");
    autoSim::simulateVaccinatie(c_, strStrm, 2);
    EXPECT_FALSE(strStrm.str().empty());
    EXPECT_EQ(135, c_->getEerste());
    EXPECT_EQ(135, c_->getGevaccineerd());
    EXPECT_EQ(0, c_->getVaccins());
}

TEST_F(simulationSimTests, hubRestock) {
    vector<Vaccine*> vacVec = h_->getVaccins();
    autoSim::simulateHubDelivery(&vacVec, 3);
    EXPECT_EQ(2000, h_->accessorTotaleVoorraad());
}

TEST_F(simulationSimTests, autoSimulation) {
    v_->setVoorraad(0);
    autoSim::simulate(sim_, 3, null_stream);
    EXPECT_EQ(685, h_->accessorTotaleVoorraad());
    EXPECT_EQ(15, c_->getVaccins());
    EXPECT_EQ(100, c_->getGevaccineerd());
    EXPECT_EQ(200, c_->getEerste());
    autoSim::simulate(sim_, 10, null_stream);
    EXPECT_EQ(500, c_->getGevaccineerd());
    EXPECT_EQ(500, c_->getEerste());
    EXPECT_EQ(35, c_->getVaccins());
    EXPECT_EQ(2965, h_->accessorTotaleVoorraad());
}
