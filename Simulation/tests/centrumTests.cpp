/**
 * \n University of Antwerp - BA1 Informatica - Project Software Engineering 2021
 * \n Test the centrum logic functions
 *
 * @authors Frederic Hamelink & Sander Marinus
 * @date    28/4/2021
 * @version 1.0
 */

#include <gtest/gtest.h>

#include "../Centrum.h"
#include "../Vaccine.h"

class centrumTests : public ::testing::Test {
protected:

    virtual void SetUp() {
        c_ = new Centrum("naam", "adres", 500, 100);
        v_ = new Vaccine("vac", 1000, 2, 45, 1, 2);
    }
    virtual void TearDown() {
    }

    // Variables to use in the tests
    Centrum* c_;
    Vaccine* v_;
};

TEST_F(centrumTests, checkSetup) {
    EXPECT_EQ(1000, v_->getVoorraad());
    EXPECT_EQ(unsigned (0), c_->getVoorraad().size());
    EXPECT_EQ(0, c_->getVaccins());
}

TEST_F(centrumTests, firstLoads) {
    // Normal transport
    EXPECT_EQ(3, c_->berekenEerstePrikLadingen(v_, 0, 1000));
    // Maximum of 200 vaccines per center until next interval
    EXPECT_EQ(2, c_->berekenEerstePrikLadingen(v_, 0, 200));
    // Negative temperature
    v_->setTemperatuur(-4);
    EXPECT_EQ(2, c_->berekenEerstePrikLadingen(v_, 0, 1000));
}

TEST_F(centrumTests, secondLoads) {
    EXPECT_EQ(3, c_->berekenTweedePrikLadingen(v_, 100));

    EXPECT_EQ(4, c_->berekenTweedePrikLadingen(v_, 500));

    v_->setTemperatuur(-4);
    EXPECT_EQ(2, c_->berekenTweedePrikLadingen(v_, 100));
}