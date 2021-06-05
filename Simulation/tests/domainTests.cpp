/**
 * \n University of Antwerp - BA1 Informatica - Project Software Engineering 2021
 * \n Tests the constructors and contracts
 *
 * @authors Frederic Hamelink & Sander Marinus
 * @date    15/3/2021
 * @version 1.0
 */

#include <gtest/gtest.h>

#include "../simulation.h"
#include "../Hub.h"
#include "../Centrum.h"
#include "../Vaccine.h"

// Test environment
// Resembles a set of tests
class simulationDomTests : public ::testing::Test {
protected:

    virtual void SetUp() {
        c_ = new Centrum("naam", "adres", 10, 2);
        v_ = new Vaccine();
        map<string, Centrum*> cMap;
        cMap.insert(pair<string, Centrum*>("naam", c_));
        vector<Vaccine*> vaccines;
        vaccines.push_back(v_);
        h_ = new Hub(vaccines, cMap);

        vector<Hub*> hubs;
        hubs.push_back(h_);

        sim_.setHubs(hubs);
        sim_.addCentrum(c_);
    }
    virtual void TearDown() {
    }

    // Variables to use in the tests
    simulation sim_;
    Centrum* c_;
    Vaccine* v_;
    Hub* h_;
};

TEST_F(simulationDomTests, simulationConstructor) {
    EXPECT_TRUE(sim_.properlyInitialised());
    EXPECT_EQ(h_, sim_.getHub());
    EXPECT_EQ(c_, sim_.getCentra()[0]);
}

TEST_F(simulationDomTests, simulationViolations) {
    vector<Centrum*> centra;
    EXPECT_DEATH(sim_.setCentra(centra), "Assertion.*failed");
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
    EXPECT_EQ(0, h_->accessorTotaleVoorraad());
    long unsigned int i = 1;
    EXPECT_EQ(i, h_->getCentra().size());
    EXPECT_EQ(c_, h_->getCentra().find("naam")->second);
    EXPECT_EQ(i, h_->getVaccins().size());
    EXPECT_EQ(v_, h_->getVaccins()[0]);
}

TEST_F(simulationDomTests, hubViolations) {
    map<string, Centrum*> cMap;
    EXPECT_DEATH(h_->setCentra(cMap), "Assertion.*failed");
    vector<Vaccine*> vaccines;
    EXPECT_DEATH(h_->setVaccins(vaccines), "Assertion.*failed");
}

TEST_F(simulationDomTests, vaccineConstructor) {
    EXPECT_TRUE(v_->properlyInitialised());
    EXPECT_EQ("", v_->getType());
    EXPECT_EQ(0, v_->getLevering());
    EXPECT_EQ(0, v_->getInterval());
    EXPECT_EQ(0, v_->getTransport());
    EXPECT_EQ(0, v_->getVoorraad());
    EXPECT_EQ(0, v_->getHernieuwing());
    EXPECT_EQ(0, v_->getTemperatuur());
}

TEST_F(simulationDomTests, vaccineViolations) {
    EXPECT_DEATH(v_->setLevering(-10), "Assertion.*failed");
    EXPECT_DEATH(v_->setInterval(-10), "Assertion.*failed");
    EXPECT_DEATH(v_->setTransport(0), "Assertion.*failed");
    EXPECT_DEATH(v_->setVoorraad(-10), "Assertion.*failed");
    EXPECT_DEATH(v_->setHernieuwing(-10), "Assertion.*failed");
}
