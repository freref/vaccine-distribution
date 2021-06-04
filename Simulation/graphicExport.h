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
     * @param c:    Center for which to calculate color
     * @return      {red, green, blue} as doubles between 0 and 1
     */
    static vector<double> calculateGradient(int maxVal, int curVal);

    /**
     \n Creates the ini file for a given day in the simulation
     * @param transports:   Map containing amount of transports to the centers
     * @param day:          Day in the simulation
     * @param path:         Path to directory for ini files
     */
    static void createIni(const Hub *hub, unsigned int hubNum, map<Centrum *, int> &transports, int day,
                          const string &path);

    static void iniAddColorSegment(string colorType, double red, double green, double blue, ofstream& oFile);

    static void iniAddHub(const Hub *h, int figNum, ofstream &oFile);

    static int iniAddHubStock(const Hub *h, int figNum, int stockDivide, int sOffset, ofstream& oFile);

    /**
     \n Adds a center to the ini file
     * @param c:        Center to be added
     * @param cNum:     Number of the center
     * @param figNum:   Amount of already added figures
     * @param cOffset:  Offset between the enters
     * @param oFile:    File to add to
     */
    static void iniAddCenter(Centrum *c, int cNum, int figNum, int cOffset, ofstream &oFile);

    /**
     \n Adds an amount of transports to the ini file
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
     * @param figAmount:    Amount of figures in ini
     * @param cAmount:      Amount of centers in ini
     * @param maxTrans:     Highest amount of transports to center
     * @param cOffset:      Offset between centers
     * @param oFile:        File to add to
     */
    static void iniGeneral(int figAmount, int cAmount, int maxTrans, int cOffset, ofstream &oFile);
};


#endif //PROJECTPSE_GRAPHICEXPORT_H
