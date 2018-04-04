#ifndef CAL_T4GA4_LOCATION_H
#define CAL_T4GA4_LOCATION_H

class Location {
private:

public:
    double dLon;
    double dLat;
    double rLon;
    double rLat;
//    double getDLAT(){return this->dLat;}
//    double getDLON(){return this->dLon;}
//    double getRLON(){return this->rLon;}
//    double getRLAT(){return this->rLat;}
  Location(double dLon, double dLat, double rLon, double rLat);
  double getLongitudeInDegrees();
  double getLatitudeInDegrees();
};

#endif //CAL_T4GA4_LOCATION_H
