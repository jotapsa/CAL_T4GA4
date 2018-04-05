#ifndef _BUILDING_H_
#define _BUILDING_H_

#include "Node.h"

class Place{
protected:
  unsigned long id;
  std::pair<double, double> coordinates;
public:
  Place(unsigned long id);
  Place(unsigned long id, std::pair<double, double> coordinates);
  unsigned long getId();
  std::pair<double, double> getCoordinates();
};

#endif /* _BUILDING_H_ */
