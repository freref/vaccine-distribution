//
// Created by sande on 13/05/2021.
//

#ifndef PROJECTPSE_GRAPHICEXPORT_H
#define PROJECTPSE_GRAPHICEXPORT_H

#include <fstream>
#include <vector>

#include "simulation.h"
#include "Centrum.h"

using namespace std;

class graphicExport {
public:
    /**
     \n Calculates to color for a given center depending on the stock
     \n Gradient from red to green
     \n REQUIRE(curVal <= maxVal, "current value can't be biggger than maximum value")
     \n REQUIRE(maxVal >= 0, "maximum value must be positive for gradient")
     \n REQUIRE(curVal >= 0, "current value must be positive for gradient")
     \n ENSURE(color.size() == unsigned (3), "didn't create all colors")
     \n ENSURE(0 <= color[0] <= 1, "red value must be 0, 1 or inbetween")
     \n ENSURE(0 <= color[1] <= 1, "green value must be 0, 1 or inbetween")
     \n ENSURE(0 <= color[2] <= 1, "blue value must be 0, 1 or inbetween")
     * @param c:    Center for which to calculate color
     * @return      {red, green, blue} as doubles between 0 and 1
     */
    static vector<double> calculateGradient(int maxVal, int curVal);

    /**
     \n Creates the ini file for a given day and hub in te simulation
     \n REQUIRE(hub->properlyInitialised(), "hub wasn't initialised when creating ini")
     \n REQUIRE(hubNum >= 0, "hub number can't be negative")
     \n REQUIRE(stockDivide > 0, "stock division must be bigger than 1")
     \n REQUIRE(day >= 0, "day can't be negative")
     * @param hub:          Hub for which to create ini
     * @param hubNum:       Number of the hub
     * @param stockDivide:  Amount of vaccines per vaccine figure in graphical export
     * @param transports:   All transports that happened that day from the hub
     * @param day:          Day of the simulation
     * @param path:         Path to output location (ending on '/')
     */
    static void createIni(const Hub *hub, unsigned int hubNum, int stockDivide, map<Centrum *, int> &transports,
                          int day, const string &path);

    /**
     \n Adds a segment for a 3d vector 'type = (x, y, z)' to the file
     \n REQUIRE(!type.empty(), "type value can't be empty for ini vector")
     * @param type:     Type of the vector
     * @param x:        x value
     * @param y:        y value
     * @param z:        z value
     * @param oFile:    File to output to
     */
    static void iniAdd3dVectorSegment(string type, double x, double y, double z, ofstream& oFile);

    /**
     \n Add representation of the hub to the ini
     \n REQUIRE(figNum >= 0, "figure can't have negative value")
     * @param figNum:   Current figure number
     * @param oFile:    File to output to
     */
    static void iniAddHub(int figNum, ofstream &oFile);

    /**
     \n Add figure per X amount of vaccines in the hub
     \n REQUIRE(h->properlyInitialised(), "hub must be initialised when adding stock to ini")
     \n REQUIRE(figNum >= 0, "figure number can't be negative")
     \n REQUIRE(stockDivide > 0, "stock divide must be positive")
     \n REQUIRE(sOffset > 0, "offset between stock must be bigger than 0")
     \n ENSURE(figNum >= 0, "iniAddHubStock postcondition failed")
     * @param h:            Pointer to hub
     * @param figNum:       Number of current figure
     * @param stockDivide:  Amount of vaccines per new figure
     * @param sOffset:      Offset between vaccine figures
     * @param oFile:        File to output to
     * @return          New figure number
     */
    static int iniAddHubStock(const Hub *h, int figNum, int stockDivide, int sOffset, ofstream& oFile);

    /**
     \n Adds a center to the ini file
     \n REQUIRE(c->properlyInitialised(), "centrum was't initialised when adding to ini")
     \n REQUIRE(cNum >= 0, "center number can't be negative")
     \n REQUIRE(figNum >= 0, "figure number can't be negative")
     \n REQUIRE(cOffset > 0, "offset between centra must be bigger than 0")
     * @param c:        Center to be added
     * @param cNum:     Number of the center
     * @param figNum:   Amount of already added figures
     * @param cOffset:  Offset between the enters
     * @param oFile:    File to add to
     */
    static void iniAddCenter(Centrum *c, int cNum, int figNum, int cOffset, ofstream &oFile);

    /**
     \n Adds an amount of transports to the ini file
     \n REQUIRE(amount >= 0, "transport amount to be added must be positive")
     \n REQUIRE(centerNum >= 0, "center number can't be negative")
     \n REQUIRE(figNum >= 0, "figure number can't be negative")
     \n REQUIRE(cOffset > 0, "offset between centra must be bigger than 0")
     \n REQUIRE(tOffset > 0, "offset between transports must be bigger than 0")
     * @param amount:       Amount of to be added transports
     * @param centerNum:    Number of center for which the transports are
     * @param figNum:       Numver of already added figures
     * @param cOffset:      Offset between the centers
     * @param tOffset:      Offset between the transports
     * @param oFile:        File to add to
     */
    static void iniAddTransports(int amount, int centerNum, int figNum, int cOffset, int tOffset, ofstream &oFile);

    /**
     \n Add the general section to the ini file
     \n REQUIRE(figAmount >= 0, "ini can't contain negative amount of figures")
     \n REQUIRE(maxTrans >= 0, "ini can't have a negative amount of maximum transports")
     * @param figAmount:    Amount of figures in ini
     * @param maxTrans:     Highest amount of transports to center
     * @param oFile:        File to add to
     */
    static void iniGeneral(int figAmount, int maxTrans, ofstream &oFile);
};


#endif //PROJECTPSE_GRAPHICEXPORT_H
