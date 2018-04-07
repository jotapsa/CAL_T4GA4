#include "Street.h"
#include "Aux.h"
#include <sstream>

unsigned long Street::idCounter = 0;

Street::Street(unsigned long ID, Place *n1, Place *n2, std::string name, EdgeType type){
    this->ID = ID;
    this->edgeID = idCounter;
    this->n1 = n1;
    this->n2 = n2;
    this->name = name;
    this->type = type;

    this->idCounter++;
}

unsigned long Street::getID() const {
    return this->ID;
}

unsigned long Street::getEdgeID() const {
    return this->edgeID;
}

EdgeType Street::getType() const {
    return this->type;
}

std::string Street::getName() const {
    return this->name;
}

Place *Street::getSource() const {
    return this->n1;
}

Place *Street::getDest() const {
    return this->n2;
}

void Street::setName(std::string name){
    this->name = name;
}

std::string Street::toString() const{
    std::stringstream street;

    street << this->ID << ";" << this->n1->getID() << ";" << this->n2->getID();

    return street.str();
}

std::string Street::getInfo() const {
    std::stringstream streetInfo;

    streetInfo << this->ID << ";" << this->name << ";" << getEdgeType(this->type);

    return streetInfo.str();
}
