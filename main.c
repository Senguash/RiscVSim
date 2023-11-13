#include "main.h"

int main(int argc, char* argv[]){
    /*char cwd[256];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Current working dir: %s\n", cwd);
    }
    else {
        perror("getcwd() error");
    }*/
    #ifdef DEBUG
    srand(time(NULL));
    DEBUG_PRINT("Executing unit tests\n");
    ExecuteAllTests();
    #endif

    readFile("../RiscVSim/addlarge.bin");
    InternalProcessorMemory ipm;
    ipm.pc = getInitPC();
    Compute(&ipm);
//    PrintRegisters(&ipm);
}
