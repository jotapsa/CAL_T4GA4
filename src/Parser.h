#ifndef _INPUTPARSER_H
#define _INPUTPARSER_H

#include "Graph.h"
#include "GarbageManagement.h"
#include <fstream>

#define PLACES_FILEPATH "../resources/nodes.txt"
#define EDGES_FILEPATH "../resources/edges.txt"
#define EDGES_INFO_FILEPATH "../resources/edges_info.txt"

#define CONTAINERS_FILEPATH "../resources/containers.txt"
#define STATIONS_FILEPATH "../resources/stations.txt"
#define GARAGES_FILEPATH "../resources/garages.txt"

bool openFile(std::fstream& file, std::string filePath);
std::vector<std::string> split(const std::string &s, const char &delim);
bool readLine(std::fstream& file, std::vector<std::string> lineVector);


//TODO: make load functions void & exit if shit hits the fan.

bool loadPlaces(GarbageManagement &management);

bool loadBuildings(GarbageManagement &management);
bool loadContainers(GarbageManagement &management);
bool loadStations(GarbageManagement &management);
bool loadGarages(GarbageManagement &management);

bool loadEdges(GarbageManagement &management);
bool loadEdgesInfo(GarbageManagement &management);

//TODO: save functions.
void saveNodes(const GarbageManagement &management);
void saveEdges(const GarbageManagement &management);
void saveEdgesInfo(const GarbageManagement &management);




#endif //_INPUTPARSER_H
