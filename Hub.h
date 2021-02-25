//
// Created by Frederic Hamelink on 25/02/2021.
//

#ifndef PROJECT_HUB_H
#define PROJECT_HUB_H

#include <string>
#include <vector>

using namespace std;

class Hub {
    int levering;
    int interval;
    int transport;
    vector<string> centra;
public:
    //constructor
    Hub(int l, int i, int t, vector<string> c){
        levering = l;
        interval = i;
        transport = t;
        centra = c;
    };

    //getters
    int getLevering(){return levering;};
    int getInterval(){return interval;};
    int getTransport(){return transport;};
    vector<string> getCentra(){return centra;};

    //setters
    void setLevering(int l){levering = l;};
    void setInterval(int i){interval = i;};
    void setTransport(int t){levering = t;};
    void setCentra(vector<string> c){centra = c;};

};


#endif //PROJECT_HUB_H
