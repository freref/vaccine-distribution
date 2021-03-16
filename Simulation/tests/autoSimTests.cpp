/**
 * University of Antwerp - BA1 Informatica - Project Software Engineering 2021
 * Tests the automatic simulation
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
        c_ = new Centrum("Centrum", "Straat 1", 500, 100);
        map<string, Centrum*> cMap;
        cMap.insert(pair<string, Centrum*>("Centrum", c_));
        h_ = new Hub(1000, 2, 75, cMap);
        sim_.setHub(h_);
        sim_.addCentrum(c_);
    }

    // Variables to use in the tests
    NullStream null_stream;
    simulation sim_;
    Centrum* c_;
    Hub* h_;
};

// The actual tests

TEST_F(simulationSimTests, // Parent test class
       correctTransport) { // Name of the test
    EXPECT_EQ(1000, h_->getVoorraad());
    EXPECT_EQ(75, h_->getTransport());
    EXPECT_EQ(0, c_->getVaccins());
    EXPECT_EQ(2, sim_.berekenLadingen(c_));
    EXPECT_EQ(0, sim_.berekenVaccinatie(c_));
    autoSim::simulateTransport(sim_, c_, null_stream);
    EXPECT_EQ(850, h_->getVoorraad());
    EXPECT_EQ(150, c_->getVaccins());
    EXPECT_EQ(0, sim_.berekenLadingen(c_));
    EXPECT_EQ(100, sim_.berekenVaccinatie(c_));
}

TEST_F(simulationSimTests, correctVaccination) {
    c_->setVaccins(200);
    EXPECT_EQ(200, c_->getVaccins());
    EXPECT_EQ(100, sim_.berekenVaccinatie(c_));
    EXPECT_EQ(0, c_->getGevaccineerd());
    autoSim::simulateVaccinatie(sim_, c_, null_stream);
    EXPECT_EQ(100, c_->getVaccins());
    EXPECT_EQ(100, sim_.berekenVaccinatie(c_));
    EXPECT_EQ(100, c_->getGevaccineerd());
}

TEST_F(simulationSimTests, autoSimulation) {
    EXPECT_EQ(1000, h_->getVoorraad());
    EXPECT_EQ(75, h_->getTransport());
    EXPECT_EQ(0, c_->getVaccins());
    EXPECT_EQ(2, sim_.berekenLadingen(c_));
    EXPECT_EQ(0, sim_.berekenVaccinatie(c_));
    autoSim::simulate(sim_, 3, null_stream);
    EXPECT_EQ(1700, h_->getVoorraad());
    EXPECT_EQ(0, c_->getVaccins());
    EXPECT_EQ(300, c_->getGevaccineerd());
    EXPECT_EQ(2, sim_.berekenLadingen(c_));
    EXPECT_EQ(0, sim_.berekenVaccinatie(c_));
    autoSim::simulate(sim_, 10, null_stream);
    EXPECT_EQ(1475, h_->getVoorraad());
    EXPECT_EQ(25, c_->getVaccins());
    EXPECT_EQ(500, c_->getGevaccineerd());
    EXPECT_EQ(0, sim_.berekenVaccinatie(c_));
}
