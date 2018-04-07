#include "Street.h"
#include <sstream>

Street::Street(unsigned long ID, Place *n1, Place *n2, std::string name, EdgeType type){
    this->ID = ID;
    this->n1 = n1;
    this->n2 = n2;
    this->name = name;
    this->type = type;
}

unsigned long Street::getID() {
    return this->ID;
}

EdgeType Street::getType(){
    return this->type;
}

std::string Street::getName() {
    return this->name;
}

std::string Street::toString() {
    std::stringstream street;

    street << this->ID << ";" << this->n1->getID() << ";" << this->n2->getID();

    return street.str();
}

std::string Street::getInfo() {
    std::stringstream streetInfo;

    streetInfo << this->ID << ";" << this->name << ";" << getEdgeType(this->type);

    return streetInfo.str();
}

void Street::setName(std::string name){
    this->name = name;
}