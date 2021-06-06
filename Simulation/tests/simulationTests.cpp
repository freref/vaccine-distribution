/**
 * \n University of Antwerp - BA1 Informatica - Project Software Engineering 2021
 * \n Tests for the simulation class
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
class simulationTests : public ::testing::Test {
protected:

    virtual void SetUp() {
        c_ = new Centrum("naam", "adres", 10, 2);
        h_ = new Hub();
    }
    virtual void TearDown() {
    }

    // Variables to use in the tests
    simulation sim_;
    Centrum* c_;
    Hub* h_;
};

TEST_F(simulationTests, checkSetup) {
    EXPECT_TRUE(sim_.properlyInitialised());

    EXPECT_EQ(unsigned (0), sim_.getHubs().size());
    EXPECT_EQ(unsigned (0), sim_.getCentra().size());
    EXPECT_EQ(unsigned (0), sim_.getDeliveries().size());
}

TEST_F(simulationTests, gettersSettersHub) {
    vector<Hub*> hubs;
    hubs.push_back(h_);
    sim_.setHubs(hubs);
    EXPECT_EQ(unsigned (1), sim_.getHubs().size());
    EXPECT_EQ(hubs, sim_.getHubs());
}

TEST_F(simulationTests, gettersSettersCentra) {
    Centrum* c = new Centrum();

    vector<Centrum*> centra;
    centra.push_back(c_);
    sim_.setCentra(centra);
    EXPECT_EQ(unsigned (1), sim_.getCentra().size());
    EXPECT_EQ(centra, sim_.getCentra());

    centra.push_back(c);
    sim_.addCentrum(c);
    EXPECT_EQ(unsigned (2), sim_.getCentra().size());
    EXPECT_EQ(centra, sim_.getCentra());
}

TEST_F(simulationTests, deliveryTests) {
    EXPECT_EQ(unsigned (0), sim_.getDeliveries().size());

    sim_.addDelivery("type", 1);
    EXPECT_EQ(unsigned (1), sim_.getDeliveries().size());
    EXPECT_EQ(1, sim_.getDeliveries()["type"]);

    sim_.addDelivery("type2", 3);
    sim_.addDelivery("type", 10);
    EXPECT_EQ(unsigned (2), sim_.getDeliveries().size());
    EXPECT_EQ(11, sim_.getDeliveries()["type"]);
    EXPECT_EQ(3, sim_.getDeliveries()["type2"]);
}

TEST_F(simulationTests, clearTest) {
    vector<Hub*> hubs;
    hubs.push_back(h_);
    vector<Centrum*> centra;
    centra.push_back(c_);

    sim_.setCentra(centra);
    sim_.setHubs(hubs);
    sim_.addDelivery("type", 100);

    EXPECT_EQ(unsigned (1), sim_.getHubs().size());
    EXPECT_EQ(unsigned (1), sim_.getCentra().size());
    EXPECT_EQ(unsigned (1), sim_.getDeliveries().size());

    sim_.clear();

    EXPECT_EQ(unsigned (0), sim_.getHubs().size());
    EXPECT_EQ(unsigned (0), sim_.getCentra().size());
    EXPECT_EQ(unsigned (0), sim_.getDeliveries().size());
}
