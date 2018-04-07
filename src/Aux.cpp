#include "Aux.h"

#include <cmath>

GarbageType getGarbageType(std::string type){
    if(type.compare(std::string("glass")) == 0){
        return GarbageType ::glass;
    }
    else if(type.compare(std::string("plastic")) == 0){
        return GarbageType ::plastic;
    }
    else if(type.compare(std::string("paper")) == 0){
        return GarbageType ::paper;
    }
    else if(type.compare(std::string("generic")) == 0){
        return GarbageType ::generic;
    }

    return GarbageType ::generic;
}

std::string getGarbageType(GarbageType type) {
    switch (type) {
        case GarbageType ::glass: {
            return std::string("glass");;
        }
        case GarbageType ::plastic: {
            return std::string("plastic");
        }
        case GarbageType ::paper: {
            return std::string("paper");
        }
        default: {
            return std::string("generic");
        }
    }
}

std::string getEdgeType(EdgeType type){
    switch (type) {
        case EdgeType::twoWay: {
            return std::string("True");;
        }
        case EdgeType::oneWay: {
            return std::string("False");
        }
    }
}

double deg2rad(double deg) {
    return deg * (M_PI / 180);
}

double getDistance(double lat1, double lon1, double lat2, double lon2) {
    double R = 6371;
    double dLat = deg2rad(lat2 - lat1);
    double dLon = deg2rad(lon2 - lon1);
    double a = sin(dLat / 2) * sin(dLat / 2)
               + cos(deg2rad(lat1)) * cos(deg2rad(lat2)) * sin(dLon / 2)
                 * sin(dLon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    double d = R * c; // Distance in km
    return d;
}

std::pair<int, int> convertToCoords(double dLat, double dLon, double rLon, double rLat) {
/*
    double distToOriginX = (dLon - MIN_LONGITUDE);
    double distToOriginy = (dLat - MIN_LATITUDE);
    auto x = (int)(distToOriginX * windowWidth / std::abs(DELTA_LONGITUDE));
    auto y = (int)(distToOriginy * windowHeight / std::abs(DELTA_LATITUDE));



    static double minY = log(tan((90 + MIN_LATITUDE) * PI / 360)) / (PI / 180);
    static double maxX = MAX_LONGITUDE * 20037508.34 / 180;
    static double maxY = log(tan((90 + MAX_LATITUDE) * PI / 360)) / (PI / 180);
    static double deltaX = maxX - minX;
    static double deltaY = maxY - minY;
    double xx = dLon * 20037508.34 / 180;
    double yy = log(tan((90 + dLat) * PI / 360)) / (PI / 180);

    yy = yy * 20037508.34 / 180;

    double distToOriginX = (xx - minX);
    double distToOriginy = (yy - minY);
    int x = (int)(distToOriginX * 1900 / deltaX);
    int y = (int)(distToOriginy * 1900 / deltaY);

    std::cout << "x= " << x << " y= " << y << std::endl;*/

//TODO(Mercator conversion)

    double x = (dLon - MIN_LONGITUDE) * IMAGE_X / DELTA_X;
    double y = (dLat - MIN_LATITUDE) * IMAGE_Y / DELTA_Y;

    return std::make_pair(400+ x,1620 -y);
}
