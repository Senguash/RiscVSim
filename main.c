#include "main.h"


int main(int argc, char* argv[]){
    /*char cwd[256];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Current working dir: %s\n", cwd);
    }
    else {
        perror("getcwd() error");
    }*/
    byte mainMem[MAIN_MEM_SIZE];
    readFile("../RiscVSim/addlarge.bin");

    InternalProcessorMemory ipm;
    ipm.exitInvoked = 0;
    ipm.pc = getInitPC(mainMem);
    Compute(&ipm);
}
