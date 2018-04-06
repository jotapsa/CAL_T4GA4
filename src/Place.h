#ifndef _BUILDING_H_
#define _BUILDING_H_

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

    static unsigned long getUnusedId();

    bool operator==(const Place& o);
};

#endif /* _BUILDING_H_ */
