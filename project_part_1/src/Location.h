//
// Created by dnc on 31-03-2018.
//

#ifndef CAL_T4GA4_LOCATION_H
#define CAL_T4GA4_LOCATION_H

class DegreeLocation {
private:
  double dLat;  //Latitude in degrees
  double dLon;  //Longitude in degrees
public:
  DegreeLocation(double lon, double lat);
  double getLon();
  double getLat();
  friend class Location;

};

class RadiansLocation {
private:
  double rLat;  //Latitude in radians
  double rLon;  //Longitude in radians
public:
  RadiansLocation(double lon, double lat);
  double getLon();
  double getLat();
  friend class Location;
};


class Location {
private:
  DegreeLocation dLocation;
  RadiansLocation rLocation;
public:
  DegreeLocation getLocationInDegrees();
  RadiansLocation getLocationInRadians();
};



#endif //CAL_T4GA4_LOCATION_H
