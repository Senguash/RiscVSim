#include "main.h"

int main(int argc, char* argv[]){
    #ifdef DEBUG
    srand(time(NULL));
    DEBUG_PRINT("Executing unit tests\n");
    ExecuteAllTests();
    #endif

    if(argc == 1) {// no args, run all test files
        char filePath[50];
        FILE *fpTests;
        fpTests = fopen("tests/tests.txt", "r");
        while (1) {
            //reads file with paths to all test and run them
            char testfile[] = "../RiscVSim/";
            fscanf(fpTests, "%s", filePath);
            if (feof(fpTests)) {
                break;
            }
            strcat(testfile, filePath);

            printf("\n Running test located at : %s\n \n", testfile);

            readFile(testfile);//loads to mem
            InternalProcessorMemory ipm;
            ipm.pc = getInitPC();//inits pc
            Compute(&ipm);//run processor
            PrintRegisters(&ipm);//print and dum regs
            DumpRegisters(&ipm,testfile);
        }
    } else{// run the files given as args
        for (int i = 1; i < argc; ++i) {
            printf("\n Running test located at : %s\n \n", argv[i]);
            readFile(argv[i]);
            InternalProcessorMemory ipm;
            ipm.pc = getInitPC();
            Compute(&ipm);
            PrintRegisters(&ipm);
            DumpRegisters(&ipm, argv[i]);

        }
    }
}
