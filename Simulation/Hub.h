//
//

#ifndef PROJECT_HUB_H
#define PROJECT_HUB_H

#include <string>
#include <vector>
#include <map>

using namespace std;

class Centrum;

class Hub {
    int levering;
    int voorraad;
    int interval;
    int transport;
    map<string, Centrum*> centra;
public:
    //constructor
    Hub() {};
    Hub(int l, int i, int t, map<string, Centrum*> c){
        levering = l;
        voorraad = l;
        interval = i;
        transport = t;
        centra = c;
    };

    //setters
    void setLevering(int l) {levering = l;};
    void setVoorraad(int v) {voorraad = v;};
    void setInterval(int i) {interval = i;};
    void setTransport(int t) {transport = t;};
    void setCentra(const map<string, Centrum*>& c) {centra = c;};

    //getters
    int getLevering() const {return levering;};
    int getVoorraad() const {return voorraad;};
    int getInterval() const {return interval;};
    int getTransport() const {return transport;};
    map<string, Centrum*> getCentra() const {return centra;};
};


#endif //PROJECT_HUB_H
