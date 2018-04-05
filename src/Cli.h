#ifndef _CLI_H
#define _CLI_H

#include "GarbageManagement.h"

bool readConfirmation();
unsigned int nextUnsignedInt(std::string str, unsigned int ceilling);

unsigned int mainMenuDialog();
unsigned int nodeMenuDialog();
unsigned int edgeMenuDialog();
unsigned int vehicleMenuDialog();
unsigned int settingsMenuDialog();

void mainMenu(GarbageManagement &management);
void nodeMenu(GarbageManagement &management);
void vehicleMenu(GarbageManagement &management);
void settingsMenu(GarbageManagement &management);
void edgeMenu(GarbageManagement &management);

void addSimpleLocation(GarbageManagement &management);

#endif //_CLI_H
