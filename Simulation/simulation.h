/**
 * \n University of Antwerp - BA1 Informatica - Project Software Engineering 2021
 * \n Class which stores and handles the simulation
 *
 * @authors Frederic Hamelink & Sander Marinus
 * @date    9/3/2021
 * @version 1.0
 */

#ifndef PROJECTPSE_SIMULATION_H
#define PROJECTPSE_SIMULATION_H

#include <vector>
#include "Vaccine.h"

using namespace std;

// Forward declaration of necessary classes
class Hub;
class Centrum;


class simulation {
    Hub* hub;
    vector<Centrum*> centra;
    simulation* _initCheck;
public:
    /**
     \n Constructor
     \n ENSURE(this->properlyInitialised(), "constructor must end properlyInitialised");
     */
    simulation();
    /**
     \n Destructor
     */
    ~simulation();
    /**
     \n Initialisation check
     * @return  Whether class is initialised
     */
    bool properlyInitialised() const;

    /**
     \n Clears the simulation class
     \n REQUIRE(this->properlyInitialised(), "simulation wasn't initialised when calling clear")
     \n ENSURE(getHub() == NULL && getCentra().empty(), "clear postconditions failed")
     */
    void clear();

    /**
     \n Sets the hub in the simulation
     \n REQUIRE(this->properlyInitialised(), "simulation wasn't initialised when calling setHub")
     \n REQUIRE(h->properlyInitialised(), "hub wasn't initialised when calling setHub")
     \n ENSURE(getHub() == h, "setHub postconditions failed")
     *  @param h The hub to be added
     */
    void setHub(Hub* const h);
    /**
     \n Add a centrum to the centra in the simulation
     \n REQUIRE(this->properlyInitialised(), "simulation wasn't initialised when calling addCentrum")
     \n REQUIRE(c->properlyInitialised(), "centrum wasn't initialised when calling addCentrum")
     \n ENSURE(getCentra().size() == oSize+1, "addCentrum postconditions failed")
     *  @param c    to be added centra
     */
    void addCentrum(Centrum* c);
    /**
     \n Set all centra in simulation
     \n REQUIRE(this->properlyInitialised(), "simulation wasn't initialised when calling setCentra")
     \n REQUIRE(!c.empty(), "simulations must contain at least 1 centrum")
     \n ENSURE(getCentra().size() == c.size(), "setCentra postcondition failed")
     *  @param c    The vector containing to ba added centra
     */
    void setCentra(const vector<Centrum*>& c);

    /**
     \n Get the simulations hub
     \n REQUIRE(this->properlyInitialised(), "simulation wasn't initialised when calling getHub")
     *  @return The hub
     */
    Hub* getHub() const;
    /**
     \n Get the centra in the simulation
     \n REQUIRE(this->properlyInitialised(), "simulation wasn't initialised when calling getCentra")
     *  @return The centra
     */
    const vector<Centrum*> &getCentra() const;

    // Transport functies
    /**
     \n Calculate amount of needed loads for transport
     \n REQUIRE(this->properlyInitialised(), "simulation wasn't initialised when calling berekenLadingen")
     \n REQUIRE(centrum->properlyInitialised(), "centrum was not initialised when calling berekenLadigen")
     *  @param centrum  Destination centrum
     *  @return         Amount of loads
     */
    int berekenLadingen(Centrum* centrum, Vaccine* vaccin) const;
    /**
     \n Increases amount of vaccins in the hub
     \n REQUIRE(getHub()->properlyInitialised(), "hub wasn't properly initialised when calling verhoogVaccinsHub")
     \n REQUIRE(vaccins>=0, "vaccins amount must be positive")
     * @param vaccins   Amount of vaccins to add
     */
    void verhoogVaccinsHub(int vaccins);
    /**
     \n Decrease the amount of vaccins in the hub
     \n REQUIRE(getHub()->properlyInitialised(), "hub wasn't initialised when calling verlaagVaccinsHub")
     \n REQUIRE(vaccins >= 0, "vaccins amount must be positive")
     \n ENSURE(getHub()->getVoorraad() == before-vaccins && getHub()->getVoorraad() >= 0,
                "verlaagVaccinsHub postconditions failed")
     * @param vaccins   Amount of vaccins to be subtracted
     */
    void verlaagVaccinsHub(int vaccins);
    /**
     \n Increases the amount of vaccins in the centrum
     \n REQUIRE(centrum->properlyInitialised(), "centrum wasn't initialised when calling verhoogVaccinsCentrum")
     \n REQUIRE(vaccins>=0, "vaccins amount must be positive")
     \n ENSURE(centrum->getVaccins() == oAmount+vaccins && centrum->getVaccins() <= centrum->getCapaciteit()*2,
                "verhoogVaccinsCentrum postconditions failed")
     * @param centrum   Centrum where to increase vaccins
     * @param vaccins   Amount of vaccins to add
     */
    static void verhoogVaccinsCentrum(Centrum* centrum, int vaccins);
    /**
     \n Prints the transport
     \n REQUIRE(centrum->properlyInitialised(), "centrum wasn't initialised when calling printTransport")
     \n REQUIRE(vaccins >= 0, "vaccins amount can't be negative")
     \n REQUIRE(vaccins%getHub()->getTransport() == 0, "vaccins amount must be multiple of transport in hub")
     * @param centrum   The destination centrum
     * @param vaccins   The amount of transported vaccins
     * @param onStream  The output stream
     */
    void printTransport(Centrum* centrum, int vaccins,Vaccine* vaccin, ostream& onStream) const;

    // Vaccinatie functies
    /**
     \n Calculate the amount of vaccins that can be given in a centrum
     \n REQUIRE(centrum->properlyInitialised(), "centrum was not initialised when calling berekenVaccinatie")
     \n ENSURE(result>=0 && result <= centrum->getCapaciteit(), "berekenVaccinatie postconditions failed")
     * @param centrum   The centrum for which to calculate the amount
     * @return          The amount of vaccins
     */
    static int berekenVaccinatie(Centrum* centrum);
    /**
     \n Decrease the amount of vaccins in a given centrum
     \n REQUIRE(centrum->properlyInitialised(), "centrum wasn't initialised when calling verlaagVaccinsCentrum")
     \n REQUIRE(vaccins>=0, "vaccins amount must be positive")
     \n ENSURE(centrum->getVaccins() == oAmount-vaccins && centrum->getVaccins() >= 0,
                "verlaagVaccinsCentrum postconditions failed")
     * @param centrum   Centrum in which to decrease the amount
     * @param vaccins   Amount of vaccins to subtract
     */
    static void verlaagVaccinCentrum(Centrum* centrum, int vaccins);
    /**
     \n Increase the amount of vaccinated people in a center
     \n REQUIRE(centrum->properlyInitialised(), "centrum wasn't initialised when calling verhoogVaccinaties")
     \n REQUIRE(vaccins >= 0, "vaccins amount must be positive")
     \n ENSURE(centrum->getGevaccineerd() <= centrum->getInwoners(),
                "verhoogVaccinaties postconditions failed");
     * @param centrum   Centrum in which to increase amount
     * @param vaccins   Amount of vaccinated people
     */
    static void verhoogVaccinaties(Centrum* centrum, int vaccins);
    /**
     \n Prints the vaccinations
     \n REQUIRE(centrum->properlyInitialised(), "centrum wasn't initialised when calling printVaccinatie")
     \n REQUIRE(vaccins >= 0, "vaccinated amount can't be negative")
     \n REQUIRE(vaccins <= centrum->getCapaciteit(), "vaccinated ammount can't exceed capacity")
     * @param centrum   Centrum in which the vaccination took place
     * @param vaccins   Amount of vaccinated people
     * @param onStream  Output stream
     */
    static void printVaccinatie(Centrum* centrum, int vaccins, ostream& onStream);
};


#endif //PROJECTPSE_SIMULATION_H
