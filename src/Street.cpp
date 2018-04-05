#include "Street.h"

Street::Street(Place *n1, Place *n2, std::string name) {
    this->n1 = n1;
    this->n2 = n2;
    this->name = name;
}

std::string Street::getName() {
    return this->name;
}

void Street::setName(std::string name){
    this->name = name;
}
