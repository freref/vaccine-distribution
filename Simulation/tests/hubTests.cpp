/**
 * \n University of Antwerp - BA1 Informatica - Project Software Engineering 2021
 * \n Tests for the Hub class
 *
 * @authors Frederic Hamelink & Sander Marinus
 * @date    5/6/2021
 * @version 2.0
 */

#include <gtest/gtest.h>

#include "../Centrum.h"
#include "../Hub.h"
#include "../Vaccine.h"

class hubTests : public ::testing::Test {
protected:

    virtual void SetUp() {
        c_ = new Centrum("naam", "adres", 500, 100);
        v_ = new Vaccine("vac", 1000, 2, 45, 1, 2);

        vector<Vaccine*> vacines;
        vacines.push_back(v_);
        map<string, Centrum*> centra;
        centra[c_->getNaam()] = c_;

        h_ = new Hub(vacines, centra);
    }
    virtual void TearDown() {
        delete c_;
        delete h_;
    }

    // Variables to use in the tests
    Centrum* c_;
    Vaccine* v_;
    Hub* h_;
};

// Check whether setup is correct
TEST_F(hubTests, checkSetup) {
    EXPECT_TRUE(h_->properlyInitialised());

    map<string , Centrum*> centra = h_->getCentra();
    EXPECT_EQ(unsigned (1), centra.size());
    EXPECT_EQ(c_, centra["naam"]);

    vector<Vaccine*> vaccines = h_->getVaccins();
    EXPECT_EQ(unsigned (1), vaccines.size());
    EXPECT_EQ(v_, vaccines[0]);
}

// Check getters/setters for centra in hub
TEST_F(hubTests, gettersSettersCentra) {
    Centrum* c = new Centrum("center2", "adres2", 100, 20);
    h_->addCentrum(c);

    map<string, Centrum*> centra;
    centra["naam"] = c_;
    centra["center2"] = c;
    EXPECT_EQ(unsigned (2), h_->getCentra().size());
    EXPECT_EQ(centra, h_->getCentra());

    centra.erase("naam");
    h_->setCentra(centra);
    EXPECT_EQ(unsigned (1), h_->getCentra().size());
    EXPECT_EQ(centra, h_->getCentra());

    delete c;
}

// Check getters/setters for vaccines in hub
TEST_F(hubTests, gettersSettersVaccines) {
    Vaccine* v = new Vaccine("vac2", 500, 1, 20, 5, -3);
    vector<Vaccine*> vaccines;
    vaccines.push_back(v_);
    vaccines.push_back(v);
    h_->addVaccine(v);
    EXPECT_EQ(unsigned (2), h_->getVaccins().size());
    EXPECT_EQ(vaccines, h_->getVaccins());

    vaccines.erase(vaccines.begin());
    h_->setVaccins(vaccines);
    EXPECT_EQ(unsigned (1), h_->getVaccins().size());
    EXPECT_EQ(vaccines, h_->getVaccins());
}

// Check getters/setters for the vaccine stock
TEST_F(hubTests, vaccineStock) {
    Vaccine* v = new Vaccine("vac2", 500, 1, 20, 5, -3);
    h_->addVaccine(v);

    h_->setVoorraad(v_, 1000);
    EXPECT_EQ(1000, h_->getVoorraad(v_));

    h_->verhoogVoorraad(v_, 500);
    EXPECT_EQ(1500, h_->getVoorraad(v_));

    h_->verlaagVoorraad(v_, 250);
    EXPECT_EQ(1250, h_->getVoorraad(v_));

    h_->setVoorraad(v, 750);
    EXPECT_EQ(2000, h_->getTotaleVoorraad());
}