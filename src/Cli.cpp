#include "Cli.h"
#include <iostream>

bool readConfirmation() {
    std::string temp;
    do{
        std::cout << "[Y/n]: ";
        getline(std::cin, temp);
    }while(temp != "Y" &&
           temp !="y" &&
           temp != "N" &&
           temp != "n");

    if(temp == "Y" || temp == "y"){
        return true;
    }
    else{
        return false;
    }
}

double parseDouble (std::string str) {
    double number;

    do {
        std::cout << str;
        std::cin >> number;

        if(std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000, '\n'); //clean input buffer
            continue;
        }
        else {
            std::cin.clear();
            std::cin.ignore(1000,'\n'); //clean input buffer
            return number;
        }
    }while(true);
}

unsigned int nextUnsignedInt(std::string str, unsigned int ceilling){
    unsigned int number;
    do{
        std::cout << str;
        std::cin >> number;
        if(std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000, '\n'); //clean input buffer
            continue;
        }
        else if(number > ceilling){
            continue;
        }
        std::cin.clear();
        std::cin.ignore(1000,'\n'); //clean input buffer
        return number;
    }while(true);
}

unsigned int settingsMenuDialog() {

    std::cout << "Settings Menu" << std::endl;
    std::cout << "1 - Set Garage" << std::endl;
    std::cout << "2 - Set Container" << std::endl;
    std::cout << "3 - Set Station" << std::endl;
    std::cout << "4 - Fill Container" << std::endl;
    std::cout << "5 - Clear Container" << std::endl;
    std::cout << "6 - Find Container" << std::endl;
    std::cout << "0 - Back" << std::endl;

    return nextUnsignedInt("Please select: ", 6);
}

void settingsMenu(GarbageManagement &management) {
    switch (settingsMenuDialog()) {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 0:
            mainMenu(management);
            break;
        default:
            break;
    }
}

unsigned int vehicleMenuDialog(){
    std::cout << "Vehicle Menu" << std::endl;
    std::cout << "1 - Create Vehicle" << std::endl;
    std::cout << "2 - Remove Vehicle" << std::endl;
    std::cout << "3 - Add Vehicle type" << std::endl;
    std::cout << "4 - Remove Vehicle type" << std::endl;
    std::cout << "0 - Back" << std::endl;

    return nextUnsignedInt("Please select: ", 4);
}

void vehicleMenu(GarbageManagement &management){
    switch(vehicleMenuDialog()){
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 0:
            mainMenu(management);
            break;
        default:
            break;
    }
}

unsigned int edgeMenuDialog(){
    std::cout << "Edge Menu" << std::endl;
    std::cout << "1 - Create Edge" << std::endl;
    std::cout << "2 - Remove Edge" << std::endl;
    std::cout << "0 - Exit" << std::endl;

    return nextUnsignedInt("Please select: ", 2);
}

void edgeMenu(GarbageManagement &management) {

    switch(edgeMenuDialog()) {
        case 1:
            break;
        case 2:
            break;
        case 0:
            mainMenu(management);
            break;
        default:
            break;
    }
}

unsigned int nodeMenuDialog() {
    std::cout << "Node Menu" << std::endl;
    std::cout << "1 - Create Location" << std::endl;
    std::cout << "2 - Create Garage" << std::endl;
    std::cout << "3 - Create Container" << std::endl;
    std::cout << "4 - Create Station" << std::endl;
    std::cout << "5 - Remove Location" << std::endl;
    std::cout << "6 - Remove Garage" << std::endl;
    std::cout << "7 - Remove Container" << std::endl;
    std::cout << "8 - Remove Container" << std::endl;
    std::cout << "0 - Exit" << std::endl;

    return nextUnsignedInt("Please select: ", 8);
}

void addSimpleLocation(GarbageManagement &management) {

    double lat = parseDouble("Insert latitude: ");
    double lon = parseDouble("Insert Longitude: ");

    management.insertNodeAt(lat, lon);
}

void nodeMenu(GarbageManagement &management){
    switch(nodeMenuDialog()){
        case 1:
            addSimpleLocation(management);
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        case 0:
            break;
        default:
            break;
    }
    mainMenu(management);
}

unsigned int mainMenuDialog(){
    std::cout << "Main Menu" << std::endl;
    std::cout << "1 - Node Menu" << std::endl;
    std::cout << "2 - Edge Menu" << std::endl;
    std::cout << "3 - Vehicle Menu" << std::endl;
    std::cout << "4 - Settings Menu" << std::endl;
    std::cout << "5 - Collect Garbage" << std::endl;
    std::cout << "6 - Evaluate Connectivity" << std::endl;
    std::cout << "7 - Stress test" << std::endl;
    std::cout << "0 - Exit" << std::endl;

    return nextUnsignedInt("Please select: ", 7);
}

void mainMenu(GarbageManagement &management) {

    switch (mainMenuDialog()) {
        case 1:
            nodeMenu(management);
            break;
        case 2:
            edgeMenu(management);
            break;
        case 3:
            vehicleMenu(management);
            break;
        case 4:
            settingsMenu(management);
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 0:
            break;
        default:
            break;
    }
}
