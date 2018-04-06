#ifndef _STREET_H
#define _STREET_H

#include <string>
#include "Aux.h"
#include "Place.h"

//TODO: IDcounter
class Street {
private:
    std::string name;
    Place *n1;
    Place *n2;

public:
    Street(Place *n1, Place *n2, std::string name);

    std::string getName();

    void setName(std::string name);
};


#endif //_STREET_H
