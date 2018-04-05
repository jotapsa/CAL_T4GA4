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

//TODO:
unsigned int nodeMenuDialog(){
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


//TODO:
unsigned int edgeMenuDialog(){
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

unsigned int vehicleMenuDialog(){
    std::cout << "Vehicle Menu" << std::endl;
    std::cout << "1 - Create Vehicle" << std::endl;
    std::cout << "2 - Remove Vehicle" << std::endl;
    std::cout << "3 - Add Vehicle type" << std::endl;
    std::cout << "4 - Remove Vehicle type" << std::endl;
    std::cout << "5 - Change Vehicle garage" << std::endl;
    std::cout << "0 - Back" << std::endl;

    return nextUnsignedInt("Please select: ", 5);
}

void mainMenu(GarbageManagement &management){
    switch(mainMenuDialog()){
        case 1:
            break;
        case 2:
            break;
        case 3:
            vehicleMenu(management);
            break;
        case 0:
            break;
        default:
            break;
    }
}

void nodeMenu(GarbageManagement &management){
    switch(nodeMenuDialog()){
        case 1:
            break;
        case 0:
            break;
        default:
            break;
    }
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
        case 5:
            break;
        case 0:
            mainMenu(management);
            break;
        default:
            break;
    }
}