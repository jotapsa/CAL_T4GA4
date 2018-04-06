#include "Street.h"
#include <sstream>

unsigned long Street::idCounter = 0;

Street::Street(Place *n1, Place *n2, std::string name, EdgeType type) {
    this->id = this->idCounter;
    this->n1 = n1;
    this->n2 = n2;
    this->name = name;
    this->type = type;

    this->idCounter++;
}

unsigned long Street::getID() {
    return this->id;
}

EdgeType Street::getType(){
    return this->type;
}

std::string Street::getName() {
    return this->name;
}

std::string Street::toString() {
    std::stringstream street;

//    street <<

    return street.str();
}

std::string Street::getOriginalName(){
    if(this->name.compare(std::string("unnamed street n"))){
        return std::string();
    }
    return this->name;
}

std::string Street::getInfo() {
    std::stringstream streetInfo;

    streetInfo << this->id << ";" << getOriginalName() << ";" << (this->type == twoWay ? std::string("True") : std::string("False"));

    return streetInfo.str();
}

void Street::setName(std::string name){
    this->name = name;
}