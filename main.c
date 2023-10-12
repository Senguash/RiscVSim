#include <stdio.h>
#include <stdlib.h>

#include "memMan.h"
#include "fileReader.h"


int main(int argc, char* argv[]){
    initMem();
    word cp = getInitPC();
    readFile("C:/Users/juliu/CLionProjects/RiscVSim/addlarge.bin");
}
