#include "Street.h"

Street::Street(Node *n1, Node *n2, std::string name) {
    this->n1 = n1;
    this->n2 = n2;
}

std::string Street::getName() {
    return this->roadName;
}

void Street::setName(std::string name){
    this->roadName = name;
}
