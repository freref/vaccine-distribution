//
// Created by sande on 4/03/2021.
//

#ifndef PROJECTPSE_SIMULATION_H
#define PROJECTPSE_SIMULATION_H

#include <vector>

using namespace std;

class Hub;
class Centrum;

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
