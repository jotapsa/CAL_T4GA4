#ifndef _STREET_H
#define _STREET_H

#include <string>
#include "Aux.h"
#include "Place.h"

class Street {
private:
    unsigned long ID;
    std::string name;
    EdgeType type;
    Place *n1;
    Place *n2;

public:
    Street(unsigned long ID, Place *n1, Place *n2, std::string name, EdgeType type);

    unsigned long getID();
    EdgeType getType();
    std::string getName();
    std::string toString();
    std::string getInfo();

    void setName(std::string name);
};


#endif //_STREET_H
