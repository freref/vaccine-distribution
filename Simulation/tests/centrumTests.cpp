/**
 * \n University of Antwerp - BA1 Informatica - Project Software Engineering 2021
 * \n Test the Centrum class
 *
 * @authors Frederic Hamelink & Sander Marinus
 * @date    28/4/2021
 * @version 2.0
 */

#include <gtest/gtest.h>

#include "../Centrum.h"
#include "../Vaccine.h"
#include "../Hub.h"

class centrumTests : public ::testing::Test {
protected:

    virtual void SetUp() {
        c_ = new Centrum("naam", "adres", 500, 100);
        v_ = new Vaccine("vac", 1000, 2, 45, 1, 2);

        vector<Vaccine*> vacines;
        vacines.push_back(v_);
        map<string, Centrum*> centra;
        centra[c_->getNaam()] = c_;

        h_ = new Hub(vacines, centra);
        h_->setVoorraad(v_, 1000);
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

// Check wheter setup is correct
TEST_F(centrumTests, checkSetup) {
    EXPECT_TRUE(c_->properlyInitialised());

    EXPECT_EQ(unsigned (0), c_->getVoorraad().size());
    EXPECT_EQ(0, c_->getVoorraad()[v_]);
    EXPECT_EQ(0, c_->getVaccins());
}

// Check funtions for deliveries first injections
TEST_F(centrumTests, firstLoads) {
    // Normal transport
    EXPECT_EQ(3, c_->berekenEerstePrikLadingen(h_, v_, 0, 1000));
    // Maximum of 200 vaccines per center until next interval
    EXPECT_EQ(2, c_->berekenEerstePrikLadingen(h_, v_, 0, 200));
    // Negative temperature
    v_->setTemperatuur(-4);
    EXPECT_EQ(2, c_->berekenEerstePrikLadingen(h_, v_, 0, 1000));
}

// Check functions for deliveries second injections
TEST_F(centrumTests, secondLoads) {
    EXPECT_EQ(3, c_->berekenTweedePrikLadingen(h_, v_, 100));

    EXPECT_EQ(4, c_->berekenTweedePrikLadingen(h_, v_, 500));

    v_->setTemperatuur(-4);
    EXPECT_EQ(2, c_->berekenTweedePrikLadingen(h_, v_, 100));
}

// Check print of a transport
TEST_F(centrumTests, printTransport) {
    ostringstream oStr;
    string expected = "Er werden 2 ladingen vac (90 vaccins) getransporteerd naar naam.\n";
    c_->printTransport(90, v_, oStr);
    EXPECT_EQ(expected, oStr.str());
}

// Check prints of vaccinations
TEST_F(centrumTests, printVaccinaties) {
    ostringstream oStr;
    string expectedFirst = "Er werden 90 inwoners voor de eerste keer gevaccineerd in naam met het vac vaccin.\n";
    c_->printEersteVaccinatie(90, v_, oStr);
    EXPECT_EQ(expectedFirst, oStr.str());
    oStr.str("");

    string expectedSecond = "Er werden 90 inwoners voor de tweede keer gevaccineerd in naam met het vac vaccin.\n";
    c_->printTweedeVaccinatie(90, v_, oStr);
    EXPECT_EQ(expectedSecond, oStr.str());
}

// Check vaccination functions
TEST_F(centrumTests, vaccinatieTests) {
    c_->verhoogEerste(100);
    EXPECT_EQ(100, c_->getEerste());

    c_->zetVaccinatie(0, v_, 100);
    int gevacCount = c_->getGevac()[make_pair(0, v_)];
    EXPECT_EQ(100, gevacCount);

    c_->removeVaccinatie(0, v_);
    EXPECT_EQ(unsigned (0), c_->getGevac().size());

    c_->verhoogGevaccineerd(100);
    EXPECT_EQ(100, c_->getGevaccineerd());
}