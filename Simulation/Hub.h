/**
 * University of Antwerp - BA1 Informatica - Project Software Engineering 2021
 * Class which represents a vaccination hub
 *
 * @authors Frederic Hamelink & Sander Marinus
 * @date    25/2/2021
 * @version 1.0
 */

#ifndef PROJECT_HUB_H
#define PROJECT_HUB_H

#include <string>
#include <vector>
#include <map>

using namespace std;

class Centrum;

/**
 * Class which represents a vaccination hub in the simulation
 */
class Hub {
    Hub* _initCheck;

    int levering;
    int voorraad;
    int interval;
    int transport;
    map<string, Centrum*> centra;
public:
    //constructor
    Hub();
    Hub(int l, int i, int t, map<string, Centrum*> c);

    bool properlyInitialised() const { return _initCheck == this; }

    //setters
    void setLevering(int l);
    void setVoorraad(int v);
    void setInterval(int i);
    void setTransport(int t);
    void setCentra(const map<string, Centrum*>& c);

    //getters
    int getLevering() const;
    int getVoorraad() const;
    int getInterval() const;
    int getTransport() const;
    const map<string, Centrum*>& getCentra() const;
};


#endif //PROJECT_HUB_H
