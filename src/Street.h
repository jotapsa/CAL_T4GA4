#ifndef _STREET_H
#define _STREET_H

#include <string>
#include "Aux.h"
#include "Place.h"

class Street {
private:
    static unsigned long idCounter;
    unsigned long id;
    std::string name;
    Place *n1;
    Place *n2;

public:
    Street(Place *n1, Place *n2, std::string name);

    unsigned long getID();
    std::string getName();
    std::string toString();
    std::string getInfo();

    void setName(std::string name);
};


#endif //_STREET_H
