#ifndef _STREET_H
#define _STREET_H

#include <string>
#include "Node.h"
#include "Aux.h"

class Street {
private:
    std::string roadName;
    Node *n1;
    Node *n2;

public:
    Street(Node *n1, Node *n2, std::string name);

    std::string getName();
    Node* getFirstNode(){return this->n1;}
    Node* getSecondNode(){return this->n2;}

    void setName(std::string name);
};


#endif //_STREET_H
