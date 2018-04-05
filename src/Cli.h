#ifndef _CLI_H
#define _CLI_H

#include "GarbageManagement.h"

bool readConfirmation();

unsigned int mainMenuDialog();
unsigned int nodeMenuDialog();
unsigned int edgeMenuDialog();
unsigned int vehicleMenuDialog();

void mainMenu(GarbageManagement &management);
void nodeMenu(GarbageManagement &management);
void vehicleMenu(GarbageManagement &management);

#endif //_CLI_H
