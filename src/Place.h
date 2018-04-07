#ifndef _PLACE_H_
#define _PLACE_H_

#include <string>
#include "Node.h"

class Place{
protected:
    static unsigned long maxId;
    unsigned long id;
    double dLon, dLat, rLon, rLat;
    std::pair<int, int> coordinates;

    void updateMaxID();
public:
    Place(unsigned long id, double dLon, double dLat, double rLon, double rLat, std::pair<int, int> coordinates);

    unsigned long getID() const;
    std::pair<double, double> getCoordinates();
    std::string toString();


    static unsigned long getUnusedId();

    bool operator==(const Place& o);
};

#endif /* _PLACE_H_ */
