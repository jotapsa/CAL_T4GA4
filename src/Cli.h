#ifndef _CLI_H
#define _CLI_H

#include "GarbageManagement.h"
#include "Aux.h"

bool readConfirmation();
unsigned int nextUnsignedInt(std::string str, unsigned int ceilling);
unsigned long int getUnsignedInt(std::string str);
bool askMap(GarbageManagement &management);

double parseDouble (std::string str);
std::pair<double, double> askForLocation();
void printMainHeader(std::string title, unsigned short length);
void printTableCell(std::string info, unsigned short length, char allignment);

unsigned int mainMenuDialog();
unsigned int nodeMenuDialog();
unsigned int edgeMenuDialog();
unsigned int vehicleMenuDialog();
unsigned int editMenuDialog();
unsigned int selectGarbageTypeMenu();
unsigned int selectAlgorithmMenu();
unsigned int editNodeMenu();
unsigned int editGarageOption();
unsigned int editContainerMenu();
unsigned int editStationMenu();

void mainMenu(GarbageManagement &management);
void nodeMenu(GarbageManagement &management);
void vehicleMenu(GarbageManagement &management);
void editMenu(GarbageManagement &management);
void edgeMenu(GarbageManagement &management);
void createContainerOrStation(GarbageManagement &management, std::string type);
void createSimpleLocation(GarbageManagement &management);
void createGarage(GarbageManagement &management);
void createEdge(GarbageManagement &management);
void createVehicle(GarbageManagement &management);

void editNode(unsigned long nodeID);
void editGarageMenu(GarbageManagement &management);
void editContainerMenu(GarbageManagement &management);
void editStation(GarbageManagement &management);

void listGarages(GarbageManagement &management);
void listContainers(GarbageManagement &management);
void listStations(GarbageManagement &management);
void listAllVehicles(GarbageManagement &management);
void listAllStreets(GarbageManagement &management);

void removeBuilding(GarbageManagement &management, std::string type);
void deleteVehicle(GarbageManagement &management);

void setAlgorithmInteraction(GarbageManagement &management);
void setFillPercentageInteraction(GarbageManagement &management);

void searchContainersMenu(GarbageManagement &management);

#endif //_CLI_H
