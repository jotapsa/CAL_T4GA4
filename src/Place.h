#ifndef _BUILDING_H_
#define _BUILDING_H_

#include "Node.h"

//TODO: IDcounter

class Place{
protected:
    unsigned long id;
    double dLon, dLat, rLon, rLat;
    std::pair<int, int> coordinates;
    
public:
    explicit Place(unsigned long id);
    Place(unsigned long id, double dLon, double dLat, double rLon, double rLat, std::pair<int, int> coordinates);
    unsigned long getID() const;
    std::pair<double, double> getCoordinates();
    bool operator==(const Place& o);
};

#endif /* _BUILDING_H_ */
