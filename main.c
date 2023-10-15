#include <stdio.h>
#include <stdlib.h>

#include "memMan.h"
#include "fileReader.h"
#include "processor.h"


int main(int argc, char* argv[]){
    char cwd[256];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Current working dir: %s\n", cwd);
    }
    else {
        perror("getcwd() error");
    }
    byte mainMem[MAIN_MEM_SIZE];
    readFile("../RiscVSim/addlarge.bin");

    InternalProcessorMemory ipm;
    ipm.pc = getInitPC(mainMem);
    Compute(ipm);
}
