//
// Created by dnc on 31-03-2018.
//

#ifndef CAL_T4GA4_STREET_H
#define CAL_T4GA4_STREET_H

#include <string>


class Street {
private:
  unsigned long id;
  std::string roadName;
  bool twoWay;
public:
  Street(unsigned long id, std::string name, bool twoWay);
  unsigned long getId();
  std::string getName();
  bool isStreetTwoWay();
};


#endif //CAL_T4GA4_STREET_H
