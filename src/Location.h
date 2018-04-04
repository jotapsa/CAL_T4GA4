#ifndef CAL_T4GA4_LOCATION_H
#define CAL_T4GA4_LOCATION_H

class Location {
private:
  double dLon;
  double dLat;
  double rLon;
  double rLat;
public:
  Location(double dLon, double dLat, double rLon, double rLat);
  double getLongitudeInDegrees();
  double getLatitudeInDegrees();
};

#endif //CAL_T4GA4_LOCATION_H
