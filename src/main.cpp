#include <iostream>
#include "Cli.h"
#include "GarbageManagement.h"

int main (int argc, char* argv[]) {
    GarbageManagement management = GarbageManagement();

    std::cout << "Read stored map ?" << std::endl;
    if(readConfirmation()){
        //read files
    }

    //menu

    std::cout << "Save map ?" << std::endl;
    if(readConfirmation()){
        //save files
    }

    return 0;
}
