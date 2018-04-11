#ifndef _INPUTPARSER_H
#define _INPUTPARSER_H

#include "Graph.h"
#include "GarbageManagement.h"
#include <fstream>

#define CREATE_MAP_PATH(map) "mkdir -p ../resources/" + map
#define MAPSLIST_FILEPATH "../resources/mapsList.txt"

#define COORDS_FILEPATH(map) "../resources/" + map + "/" + map + ".txt"

#define PLACES_FILEPATH(map) "../resources/" + map + "/places.txt"
#define EDGES_FILEPATH(map) "../resources/" + map + "/edges.txt"
#define EDGES_INFO_FILEPATH(map) "../resources/" + map + "/edges_info.txt"

#define CONTAINERS_FILEPATH(map) "../resources/" + map + "/containers.txt"
#define STATIONS_FILEPATH(map) "../resources/" + map + "/stations.txt"
#define GARAGES_FILEPATH(map) "../resources/" + map + "/garages.txt"

#define VEHICLES_FILEPATH(map) "../resources/" + map + "/vehicles.txt"

bool openFile(std::fstream& file, std::string filePath);
std::vector<std::string> split(const std::string &s, const char &delim);
bool readLine(std::fstream& file, std::vector<std::string> lineVector);

bool loadCoords(GarbageManagement &management);

bool loadPlaces(GarbageManagement &management);

bool loadContainers(GarbageManagement &management);
bool loadStations(GarbageManagement &management);
bool loadVehicles(GarbageManagement &management);
bool loadGarages(GarbageManagement &management);

bool loadEdges(GarbageManagement &management);
bool loadEdgesInfo(GarbageManagement &management);

bool saveMap(const GarbageManagement &management);

void savePlaces(const GarbageManagement &management);

void saveContainers(const GarbageManagement &management);
void saveStations(const GarbageManagement &management);
void saveVehicles(const GarbageManagement &management);
void saveGarages(const GarbageManagement &management);

void saveEdges(const GarbageManagement &management);
void saveEdgesInfo(const GarbageManagement &management);

#endif //_INPUTPARSER_H
