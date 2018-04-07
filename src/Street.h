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

    unsigned long getID() const;

    std::string getName() const;
    std::string getOriginalName() const;
    EdgeType getType() const;
    Place * getSource() const;
    Place * getDest() const;


    void setName(std::string name);

    std::string toString() const;
    std::string getInfo() const;
};


#endif //_STREET_H
