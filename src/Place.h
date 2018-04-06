#ifndef _BUILDING_H_
#define _BUILDING_H_

#include "Node.h"

//TODO: IDcounter

class Place{
protected:
  unsigned long id;
  std::pair<double, double> coordinates;
public:
  Place(unsigned long id);
  Place(unsigned long id, std::pair<double, double> coordinates);
  unsigned long getID() const;
  std::pair<double, double> getCoordinates();
  bool operator==(const Place& o);
};

#endif /* _BUILDING_H_ */
