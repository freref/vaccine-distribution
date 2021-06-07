/**
 * \n University of Antwerp - BA1 Informatica - Project Software Engineering 2021
 * \n Class which represents a vaccination center
 *
 * @authors Frederic Hamelink & Sander Marinus
 * @date    25/2/2021
 * @version 1.0
 */

#ifndef PROJECT_CENTRUM_H
#define PROJECT_CENTRUM_H

#include <string>
#include <vector>
#include <map>
#include "Vaccine.h"
#include "Hub.h"

using namespace std;

/**
 * Class which represents a vaccination centre in the simulation
 */
class Centrum {
    Centrum* _initCheck;

    string naam;
    string adres;
    int inwoners;
    int capaciteit;
    int gevaccineerd;
    int eerste;
    map<Vaccine*, int> voorraad;
    map<pair<int, Vaccine*>, int> gevac;
public:
    /**
     \n Add parsed xml element data to the center
     \n REQUIRE(this->properlyInitialised(), "centrum wasn't initialised when inserting xml element")
     * @param ele:      Parsed element
     * @param errStr:   output error stream
     * @return      Succes of insert
     */
    bool insert(TiXmlElement *ele, ostream& errStr);

    /**
     \n Check wether centrum is empty
     \n REQUIRE(this->properlyInitialised(), "centrum wasn't initialised when checking empty");
     * @return
     */
    bool empty();
    //constructor
    /**
     \n Empty constructor
     \n ENSURE(this->properlyInitialised(), "constructor must end properlyInitialised")
     */
    Centrum();
    /**
     \n Constructor
     \n REQUIRE(!n.empty(), "center name can't be empty")
     \n REQUIRE(!a.empty(), "center addres can't be empty")
     \n REQUIRE(i>=0, "inhabitant amount can't be negative")
     \n REQUIRE(c>=0, "capacity can't be negative")
     \n ENSURE(this->properlyInitialised(), "constructor must end properlyInitialised");
     * @param n:    Name
     * @param a:    Adres
     * @param i:    Inhabitants amount
     * @param c:    Capacity
     */
    Centrum(const string& n, const string& a, int i, int c);

    /**
     * Checks if propperly initialized
     * @return bool properly initialised
     */
    bool properlyInitialised() const {return _initCheck == this; };

    /**
     \n set stock of certain vaccine
     \n REQUIRE(this->properlyInitialised(), "centrum wasn't initialised when calling setVoorraad")
     \n REQUIRE(vac->properlyInitialised(), "vaccine must be initialised when setting stock")
     \n REQUIRE(aantal >= 0, "vaccine can't have negative stock")
     \n REQUIRE(getVaccins() - getVoorraad()[vac] + aantal <= getCapaciteit()*2,
                "stock can't be bigger than capacity allows")
     \n ENSURE(getVoorraad()[vac] == aantal, "setVoorraad postcondition failed")
     * @param vac:      The vaccine
     * @param aantal:   Stock of the vaccine
     */
    void setVoorraad(Vaccine* vac, int aantal);
    /**
     \n Get map of vaccines and stock in center
     \n REQUIRE(this->properlyInitialised(), "centrum wasn't initialised when calling getVoorraad")
     * @return map<Vaccine*, int> {type: voorraad, ...}
     */
    map<Vaccine*, int> getVoorraad();
    /**
     \n Add to stock of vaccine
     \n REQUIRE(this->properlyInitialised(), "centrum wasn't initialised when calling verhoogVoorraad")
     \n REQUIRE(vac->properlyInitialised(), "vaccine wasn't initialised when calling verhoogVoorraad")
     \n REQUIRE(getVaccins() + aantal <= getCapaciteit()*2, "can't store more vaccines than capacity allows")
     \n ENSURE(getVoorraad()[vac]-aantal == oAmount, "verhoogVoorraad postcondition failed")
     * @param vac:      Vaccine to add stock toe
     * @param aantal:   Amount of stock to add
     */
    void verhoogVoorraad(Vaccine* vac, int aantal);
    /**
     \n Lower stock of vaccine
     \n REQUIRE(this->properlyInitialised(), "centrum wasn't initialised when calling verlaagVoorraad")
     \n REQUIRE(vac->properlyInitialised(), "vaccine wasn't initialised when calling verlaagVoorraad")
     \n REQUIRE(getVaccins() - aantal >= 0, "can't have negative stock of vaccines")
     \n REQUIRE(getVoorraad()[vac] - aantal >=0, "can't have negative stock of vaccine")
     \n ENSURE(getVoorraad()[vac]+aantal == oAmount, "verlaagVoorraad postcondition failed")
     * @param vac:      Vaccine to lower stock off
     * @param aantal:   Amount to lower
     */
    void verlaagVoorraad(Vaccine* vac, int aantal);

    /**
     \n Set amount of vaccinated people in center
     \n REQUIRE(this->properlyInitialised(), "centrum wasn't initialised when calling setGevaccineerd")
     \n REQUIRE(g>=0, "gevaccineerd can't be negative")
     \n REQUIRE(g<=getInwoners(), "gevaccineerd amount can't be bigger than inhabitants amount")
     \n ENSURE(getGevaccineerd() == g, "setGevaccineerd postcondition failed")
     * @param g:    Amount of vaccinated people
     */
    void setGevaccineerd(int g);

    /**
     \n getter for name
     \n REQUIRE(this->properlyInitialised(), "centrum wasn't initialised when calling getNaam")
     * @return string name
     */
    const string &getNaam() const;
    /**
     \n getter for address
     \n REQUIRE(this->properlyInitialised(), "centrum wasn't initialised when calling getAdres")
     * @return string address
     */
    const string &getAdres() const;
    /**
     \n getter for inhabitants
     \n REQUIRE(this->properlyInitialised(), "centrum wasn't initialised when calling setVacins")
     \n ENSURE(amount>=0, "getInwoners postconditions failed")
     * @return int inhabitants
     */
    int getInwoners() const;
    /**
     \n getter for capacity
     \n REQUIRE(this->properlyInitialised(), "centrum wasn't initialised when calling getCapaciteit")
     \n ENSURE(amount>=0, "getCapaciteit postconditions failed")
     * @return int
     */
    int getCapaciteit() const;
    /**
     \n Get total amount of vaccines in center
     \n REQUIRE(this->properlyInitialised(), "centrum wasn't initialised when calling getVaccins")
     \n ENSURE((amount>=0) && (amount<=getCapaciteit()*2), "getVaccins postconditions failed")
     * @return int
     */
    int getVaccins();
    /**
     * \n Get total amount of fully vaccinated people
     * \n REQUIRE(this->properlyInitialised(), "centrum wasn't initialised when calling getGevaccineerd")
       \n ENSURE((amount>=0) && (amount<=getInwoners()), "getGevaccineerd postconditions failed")
     * @return int
     */
    int getGevaccineerd() const;

    /**
     \n Calculate amount of shipments for first injection
     \n REQUIRE(this->properlyInitialised(), "simulation wasn't initialised when calling berekenEerstePrikLadingen")
     \n REQUIRE(hub->properlyInitialised(), "hub wasn't initialised when calling berekenEerstePrikLadingen")
     \n REQUIRE(vaccin->properlyInitialised(), "vaccine wasn't initialised when calling berekenEerstePrikLadingen")
     \n REQUIRE(dag >= 0, "transport day can't be negative")
     \n REQUIRE(devide >= 0, "division can't be negative")
     \n ENSURE(ladingen>=0, "berekenEerstePrikLadingen postconditions failed")
     * @param hub:      Hub to which center is linked
     * @param vaccin:   Vaccine to ship
     * @param dag:      Day of injection
     * @param devide:   Amount of vaccins for center until next shipment arrives in hub
     * @return          Amount of shipments
     */
    int berekenEerstePrikLadingen(Hub* hub, Vaccine* vaccin, int dag, int devide);
    /**
     \n Calculate amount of shipments for second injection
     \n REQUIRE(this->properlyInitialised(), "simulation wasn't initialised when calling berekenTweedePrikLadingen")
     \n REQUIRE(hub->properlyInitialised(), "hub wasn't initialised when calling berekenTweedePrikLadingen")
     \n REQUIRE(vaccin->properlyInitialised(), "vaccine wasn't initialised when calling berekenTweedePrikLadingen")
     \n REQUIRE(aantal >= 0, "transport can't have negative amount of vaccines")
     \n ENSURE(ladingen >= 0, "berekenTweedePrikLadingen postconditions failed")
     * @param hub:      Hub to which center is linked
     * @param vaccin:   Vaccine to ship
     * @param aantal:   Necessary amount
     * @return          Amount of shipments
     */
    int berekenTweedePrikLadingen(Hub* hub, Vaccine* vaccin, int aantal);

    /**
     \n Print a transport
     \n REQUIRE(this->properlyInitialised(), "centrum wasn't initialised when calling printTransport")
     \n REQUIRE(vaccin->properlyInitialised(), "vaccine wasn't initialised when calling printTransport")
     \n REQUIRE(vaccins >= 0, "can't transport negative amount of vaccines")
     * @param vaccins:  Amount of transported vaccines
     * @param vaccin:   Transported vaccine
     * @param onStream: Output stream
     */
    void printTransport(int vaccins, Vaccine* vaccin, ostream& onStream) const;
    /**
     \n Print a first vaccination
     \n REQUIRE(this->properlyInitialised(), "centrum wasn't initialised when calling printEersteVaccinatie")
     \n REQUIRE(vaccin->properlyInitialised(), "vaccine wasn't initialised when calling printEersteVaccinatie")
     \n REQUIRE(vaccinaties >= 0, "can't vaccinate negative amount of people")
     * @param vaccins:  Amount of vaccinated people
     * @param vaccin:   Used vaccine
     * @param onStream: Output stream
     */
    void printEersteVaccinatie(int vaccins,Vaccine* vaccin, ostream& onStream) const;
    /**
     \n Print a second vaccination
     \n REQUIRE(this->properlyInitialised(), "centrum wasn't initialised when calling printTweedeVaccinatie")
     \n REQUIRE(vaccin->properlyInitialised(), "vaccine wasn't initialised when calling printTweedeVaccinatie")
     \n REQUIRE(vaccins >= 0, "can't vaccinate negative amount of people")
     * @param vaccins:  Aount
     * @param vaccin
     * @param onStream
     */
    void printTweedeVaccinatie(int vaccins,Vaccine* vaccin, ostream& onStream) const;

    /**
     \n Add first vaccination information
     \n REQUIRE(this->properlyInitialised(), "centrum wasn't initialised when calling zetVaccinatie")
     \n REQUIRE(vac->properlyInitialised(), "vaccine wasn't initialised when calling zetVaccinatie")
     \n REQUIRE(dag >= 0, "day can't be negative")
     \n REQUIRE(aantal >= 0, "can't vaccinate negative amount of people")
     \n ENSURE(getGevac()[make_pair(dag, vac)] = oAmount + aantal, "zetVaccinatie postcondition failed")
     * @param dag:      Day of vaccination
     * @param vac:      Used vaccine
     * @param aantal:   Amount to vaccinate
     */
    void zetVaccinatie(int dag, Vaccine* vac, int aantal);
    /**
     \n Remove information of vaccination
     \n REQUIRE(this->properlyInitialised(), "centrum wasn't initialised when calling removeVaccinatie")
     \n REQUIRE(vac->properlyInitialised(), "vaccine wasn't initialised when calling removeVaccinatie")
     \n REQUIRE(dag >= 0, "day can't be negative")
     * @param dag:  Day of vaccination
     * @param vac:  Used vaccine
     */
    void removeVaccinatie(int dag, Vaccine* vac);

    /**
     \n Get map containing information first vaccinations
     \n REQUIRE(this->properlyInitialised(), "centrum wasn't initialised when calling getGevac")
     * @return { (dag, vaccin): aantal, ... }
     */
    map<pair<int, Vaccine*>, int> getGevac();

    /**
     \n Increase amount of fully vaccinated people
     \n REQUIRE(this->properlyInitialised(), "centrum wasn't initialised when calling verhoogGevaccineerd")
     \n REQUIRE(getGevaccineerd() + aantal <= getInwoners(),
               "amount of vaccinated people can't be more than inhabitants")
     \n ENSURE(getGevaccineerd() == oAmount + aantal, "verhoogGevaccineerd postcondition failed")
     * @param aantal:   Amount by wich to increase
     */
    void verhoogGevaccineerd(int aantal);

    /**
     \n Get amount of people with first injection
     \n REQUIRE(this->properlyInitialised(), "centrum wasn't initialised when calling getEerste")
     * @return  Amount of people
     */
    int getEerste() const ;
    /**
     \n Increase amount of people with first injection
     \n REQUIRE(this->properlyInitialised(), "centrum wasn't initialised when calling verhoogEerste")
     \n REQUIRE(getEerste() + aantal <= getInwoners(),
                "amount of people with first injection can't be more than inhabitants")
     \n ENSURE(getEerste() == oAmount + aantal, "verhoogEerste postcondition failed")
     * @param aantal:   Amount to increase by
     */
    void verhoogEerste(int aantal);
};


#endif //PROJECT_CENTRUM_H
