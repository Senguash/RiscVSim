#include "main.h"

int main(int argc, char* argv[]){
    /*char cwd[256];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Current working dir: %s\n", cwd);
    }
    else {
        perror("getcwd() error");
    }*/
/*    #ifdef DEBUG
    srand(time(NULL));
    DEBUG_PRINT("Executing unit tests\n");
    ExecuteAllTests();
    #endif
    */
    char filePath[50];
    FILE *fpTests;
    fpTests = fopen("tests/tests.txt","r");
    while (1)
    {
    char testfile[]= "../RiscVSim/";
        fscanf(fpTests,"%s",filePath);
        if(feof(fpTests)){
            break;
        }
    strcat(testfile,filePath);
    
    printf("\n Running test located at : %s\n \n",testfile);
    
    readFile(testfile);
    InternalProcessorMemory ipm;
    ipm.pc = getInitPC();
    Compute(&ipm);
    PrintRegisters(&ipm);
    }

//    readFile("../RiscVSim/addlarge.bin");
//    InternalProcessorMemory ipm;
//    ipm.pc = getInitPC();
 //   Compute(&ipm);
    //PrintRegisters(&ipm);
}
