#ifndef _CLI_H
#define _CLI_H

#include "GarbageManagement.h"
#include <iostream>
#include "Aux.h"

bool readConfirmation();
unsigned int nextUnsignedInt(std::string str, unsigned int ceilling);
double parseDouble (std::string str);
std::pair<double, double> askForLocation();

unsigned int mainMenuDialog();
unsigned int nodeMenuDialog();
unsigned int edgeMenuDialog();
unsigned int vehicleMenuDialog();
unsigned int settingsMenuDialog();
unsigned int selectGarbageTypeMenu();

void mainMenu(GarbageManagement &management);
void nodeMenu(GarbageManagement &management);
void vehicleMenu(GarbageManagement &management);
void settingsMenu(GarbageManagement &management);
void edgeMenu(GarbageManagement &management);
void addContainer(GarbageManagement &management);
void addSimpleLocation(GarbageManagement &management);
void addGarage(GarbageManagement &management);

#endif //_CLI_H
