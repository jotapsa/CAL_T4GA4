#ifndef _CLI_H
#define _CLI_H

#include "GarbageManagement.h"
#include <iostream>
#include <iomanip>
#include "Aux.h"

bool readConfirmation();
unsigned int nextUnsignedInt(std::string str, unsigned int ceilling);
unsigned int getUnsignedInt(std::string str);
double parseDouble (std::string str);
std::pair<double, double> askForLocation();

unsigned int mainMenuDialog();
unsigned int nodeMenuDialog();
unsigned int edgeMenuDialog();
unsigned int vehicleMenuDialog();
unsigned int settingsMenuDialog();
unsigned int selectGarbageTypeMenu();
unsigned int editNodeMenu();

void mainMenu(GarbageManagement &management);
void nodeMenu(GarbageManagement &management);
void vehicleMenu(GarbageManagement &management);
void settingsMenu(GarbageManagement &management);
void edgeMenu(GarbageManagement &management);
void createContainerOrStation(GarbageManagement &management, std::string type);
void createSimpleLocation(GarbageManagement &management);
void createGarage(GarbageManagement &management);
void editNode(unsigned long nodeID);

void listGarages(GarbageManagement &management);

#endif //_CLI_H
