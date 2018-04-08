#ifndef _CLI_H
#define _CLI_H

#include "GarbageManagement.h"
#include "Aux.h"

bool readConfirmation();
unsigned int nextUnsignedInt(std::string str, unsigned int ceilling);
unsigned long int getUnsignedInt(std::string str);
double parseDouble (std::string str);
std::pair<double, double> askForLocation();

unsigned int mainMenuDialog();
unsigned int nodeMenuDialog();
unsigned int edgeMenuDialog();
unsigned int vehicleMenuDialog();
unsigned int editMenuDialog();
unsigned int selectGarbageTypeMenu();
unsigned int selectAlgorithMenu();
unsigned int editNodeMenu();
unsigned int editGarageOption();

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

void listGarages(GarbageManagement &management);
void listContainers(GarbageManagement &management);
void listStations(GarbageManagement &management);
void listAllVehicles(GarbageManagement &management);
void listAllStreets(GarbageManagement &management);

void removeBuilding(GarbageManagement &management, std::string type);
void deleteVehicle(GarbageManagement &management);

void setAlgorithmInteraction(GarbageManagement &management);
void setFillPercentageInteraction(GarbageManagement &management);

#endif //_CLI_H
