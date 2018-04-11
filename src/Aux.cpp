#include "Aux.h"

#include <cmath>
#include "Algorithm.h"

double minLatitude;
double minLongitude;
double maxLatitude;
double maxLongitude;

double delta_Latitude;
double delta_Longitude;

unsigned int imageWidth;
unsigned int imageHeight;

void updateMapCoords(std::vector<double> mapCoords, unsigned int width, unsigned int height){
    minLatitude = mapCoords.at(0);
    minLongitude = mapCoords.at(1);
    maxLatitude = mapCoords.at(2);
    maxLongitude = mapCoords.at(3);

    delta_Latitude = maxLatitude - minLatitude;
    delta_Longitude = maxLongitude - minLongitude;

    imageWidth = width;
    imageHeight = height;
}

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
            return std::string("glass");
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

std::string getGarbageTypeImgPath(GarbageType type){
    switch (type) {
        case GarbageType ::glass: {
            return glassImgPath;
        }
        case GarbageType ::plastic: {
            return plasticImgPath;
        }
        case GarbageType ::paper: {
            return paperImgPath;
        }
        default: {
            return genericImgPath;
        }
    }
}

std::string getAlgorithmName(Algorithm type) {

    switch(type) {
        case Algorithm::Dijkstra:
            return std::string("Dijkstra");
        case Algorithm::aStar:
            return std::string("A*");
        case Algorithm::Warshall:
            return std::string("Floyd Warshall");
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
//    https://www.movable-type.co.uk/scripts/latlong.html
    double R = 6371e3;

    double rLat1 = deg2rad(lat1);
    double rLat2 = deg2rad(lat2);

    double dLat = deg2rad(lat2 - lat1);
    double dLon = deg2rad(lon2 - lon1);

    double a = sin(dLat / 2) * sin(dLat / 2) +
               cos(rLat1) * cos(rLat2)
               * sin(dLon / 2) * sin(dLon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    double d = R * c;

    return d; //meters
}

std::pair<int, int> convertToCoords(double dLat, double dLon, double rLon, double rLat) {

    int x = (int)((dLon - minLongitude) * imageWidth / delta_Longitude);
    int y = (int)(imageHeight - (dLat - minLatitude) * imageHeight / delta_Latitude);

    return std::make_pair(x,y);
}

std::pair<int, int> convertToCoords(std::pair<double, double> coords) {

    int x = (int)((coords.second - minLongitude) * imageWidth / delta_Longitude);
    int y = (int)(imageHeight - (coords.first - minLatitude) * imageHeight / delta_Latitude);

    return std::make_pair(x,y);
};

bool insideWindow(std::pair<int, int> coords) {

    return coords.first < imageWidth || coords.second < imageHeight;
}

bool getImageSize(std::string imagePath, unsigned int *x, unsigned int *y){
    FILE *f=fopen(imagePath.c_str(),"rb");

    if (f == NULL){
        return false;
    }

    fseek(f,0,SEEK_END);
    long len=ftell(f);
    fseek(f,0,SEEK_SET);

    if (len<24) {
        fclose(f);
        return false;
    }

    unsigned char buf[24];
    fread(buf,1,24,f);

    fclose(f);

    if ( buf[0]==0x89 && buf[1]=='P' && buf[2]=='N' && buf[3]=='G' && buf[4]==0x0D && buf[5]==0x0A && buf[6]==0x1A && buf[7]==0x0A
         && buf[12]=='I' && buf[13]=='H' && buf[14]=='D' && buf[15]=='R') {
        *x = (buf[16]<<24) + (buf[17]<<16) + (buf[18]<<8) + (buf[19]<<0);
        *y = (buf[20]<<24) + (buf[21]<<16) + (buf[22]<<8) + (buf[23]<<0);
        return true;
    }

    return false;
}

