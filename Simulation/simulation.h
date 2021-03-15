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

    void setHub(Hub* const h) { hub = h; }
    void addCentrum(Centrum* c);
    void setCentra(const vector<Centrum*>& c) { centra = c; }

    Hub* getHub() const;
    const vector<Centrum*> &getCentra() const;
};


#endif //PROJECTPSE_SIMULATION_H
