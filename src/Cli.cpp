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
