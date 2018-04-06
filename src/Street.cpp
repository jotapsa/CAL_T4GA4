#include "Street.h"
#include <sstream>

unsigned long Street::idCounter = 0;

Street::Street(Place *n1, Place *n2, std::string name) {
    this->id = this->idCounter;
    this->n1 = n1;
    this->n2 = n2;
    this->name = name;

    this->idCounter++;
}

unsigned long Street::getID() {
    return this->id;
}

std::string Street::getName() {
    return this->name;
}

std::string Street::toString() {
    std::stringstream street;

//    street <<

    return street.str();
}

std::string Street::getInfo() {
    return std::string();
}

void Street::setName(std::string name){
    this->name = name;
}