//
// Created by dnc on 30-03-2018.
//
#include <iostream>
#include "graphviewer.h"

int main (int argc, char* argv[]) {

    GraphViewer *gv = new GraphViewer(600, 600, true);

    gv->createWindow(600, 600);

    return 0;
}