/**
 * University of Antwerp - BA1 Informatica - Project Software Engineering 2021
 * Class which stores and handles the simulation
 *
 * @authors Frederic Hamelink & Sander Marinus
 * @date    9/3/2021
 * @version 1.0
 */

#ifndef PROJECTPSE_SIMULATION_H
#define PROJECTPSE_SIMULATION_H

#include <vector>

using namespace std;

class Hub;
class Centrum;

/**
 * Class which represents a vaccination simulation
 */
class simulation {
    Hub* hub;
    vector<Centrum*> centra;
    simulation* _initCheck;
public:
    simulation();
    ~simulation();
    bool properlyInitialised() const;

    void clear();

    void setHub(Hub* const h);
    void addCentrum(Centrum* c);
    void setCentra(const vector<Centrum*>& c);

    Hub* getHub() const;
    const vector<Centrum*> &getCentra() const;

    //transport
    int berekenLadingen(Centrum* centrum) const;
    void verhoogVaccinsHub(int vaccins);
    void verlaagVaccinsHub(int vaccins);
    static void verhoogVaccinsCentrum(Centrum* centrum, int vaccins);
    void printTransport(Centrum* centrum, int vaccins, ostream& onStream) const;

    //vaccinaties
    static int berekenVaccinatie(Centrum* centrum);
    static void verlaagVaccinCentrum(Centrum* centrum, int vaccins);
    static void verhoogVaccinaties(Centrum* centrum, int vaccins);
    static void printVaccinatie(Centrum* centrum, int vaccins, ostream& onStream);
};


#endif //PROJECTPSE_SIMULATION_H
