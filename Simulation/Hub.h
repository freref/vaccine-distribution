//
// Created by Frederic Hamelink on 25/02/2021.
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
    int interval;
    int transport;
    map<string, Centrum*> centra;
public:
    //constructor
    Hub() {};
    Hub(int l, int i, int t, map<string, Centrum*> c){
        levering = l;
        interval = i;
        transport = t;
        centra = c;
    };

    //setters
    void setLevering(int l){levering = l;};
    void setInterval(int i){interval = i;};
    void setTransport(int t){levering = t;};
    void setCentra(const map<string, Centrum*>& c) {centra = c;};

    //getters
    int getLevering(){return levering;};
    int getInterval(){return interval;};
    int getTransport(){return transport;};
    map<string, Centrum*> getCentra() {return centra;};
};


#endif //PROJECT_HUB_H
