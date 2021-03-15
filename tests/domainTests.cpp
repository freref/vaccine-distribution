/**
 * University of Antwerp - BA1 Informatica - Project Software Engineering 2021
 * Tests the constructors and contracts
 *
 * @authors Frederic Hamelink & Sander Marinus
 * @date    15/3/2021
 * @version 1.0
 */

#include <gtest/gtest.h>

#include "../Simulation/simulation.h"
#include "../Simulation/Hub.h"
#include "../Simulation/Centrum.h"

// Test environment
// Resembles a set of tests
class simulationDomTests : public ::testing::Test {
protected:

    virtual void SetUp() {
        c_ = new Centrum("naam", "adres", 10, 2);
        map<string, Centrum*> cMap;
        cMap.insert(pair<string, Centrum*>("naam", c_));
        h_ = new Hub(100, 2, 3, cMap);
        sim_.setHub(h_);
        sim_.addCentrum(c_);
    }
    virtual void TearDown() {
    }

    // Variables to use in the tests
    simulation sim_;
    Centrum* c_;
    Hub* h_;
};

TEST_F(simulationDomTests, simulationConstructor) {
    EXPECT_TRUE(sim_.properlyInitialised());
    EXPECT_EQ(h_, sim_.getHub());
    EXPECT_EQ(c_, sim_.getCentra()[0]);
}

TEST_F(simulationDomTests, centrumConstructor) {
    EXPECT_TRUE(c_->properlyInitialised());
    EXPECT_EQ("naam", c_->getNaam());
    EXPECT_EQ("adres", c_->getAdres());
    EXPECT_EQ(10, c_->getInwoners());
    EXPECT_EQ(2, c_->getCapaciteit());
    EXPECT_EQ(0, c_->getVaccins());
    EXPECT_EQ(0, c_->getGevaccineerd());
}

TEST_F(simulationDomTests, hubConstructor) {
    EXPECT_TRUE(h_->properlyInitialised());
    EXPECT_EQ(100, h_->getLevering());
    EXPECT_EQ(100, h_->getVoorraad());
    EXPECT_EQ(2, h_->getInterval());
    EXPECT_EQ(3, h_->getTransport());
    long unsigned int i = 1;
    EXPECT_EQ(i, h_->getCentra().size());
    EXPECT_EQ(c_, h_->getCentra().find("naam")->second);
}

TEST_F(simulationDomTests, centrumViolations) {
    EXPECT_DEATH(c_->setVaccins(-10), "Assertion.*failed");
    EXPECT_DEATH(c_->setVaccins(c_->getCapaciteit()*2+10), "Assertion.*failed");
}

TEST_F(simulationDomTests, hubViolations) {
    EXPECT_DEATH(h_->setTransport(-10), "Assertion.*failed");
    EXPECT_DEATH(h_->setInterval(-10), "Assertion.*failed");
    EXPECT_DEATH(h_->setVoorraad(-10), "Assertion.*failed");
    EXPECT_DEATH(h_->setLevering(-10), "Assertion.*failed");
    map<string, Centrum*> cMap;
    EXPECT_DEATH(h_->setCentra(cMap), "Assertion.*failed");
}

TEST_F(simulationDomTests, simulationViolations) {
    EXPECT_DEATH(sim_.verlaagVaccinsHub(h_->getVoorraad()+10), "Assertion.*failed");
    EXPECT_DEATH(sim_.verhoogVaccinsHub(-10), "Assertion.*failed");
    EXPECT_DEATH(sim_.verlaagVaccinCentrum(c_, -10), "Assertion.*failed");
    EXPECT_DEATH(sim_.verhoogVaccinsCentrum(c_, -10), "Assertion.*failed");
    EXPECT_DEATH(sim_.verhoogVaccinaties(c_, c_->getInwoners()+10), "Assertion.*failed");
    vector<Centrum*> centra;
    EXPECT_DEATH(sim_.setCentra(centra), "Assertion.*failed");
}
