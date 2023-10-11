//
// Created by juliu on 11-10-2023.
//

#include "fileReader.h"

void readFile(char file[]){
    FILE *ptr_myfile;
    ptr_myfile=fopen(file,"rb");
    if (!ptr_myfile)
    {
        printf("Unable to open file!");
        exit(1);
    }
    initMem();
    uWord pc = getInitPC();
    byte readByte;
    while ((readByte = fgetc(ptr_myfile)) != EOF){ //todo måden filen læses på skal ændres
        setByte(readByte,pc);
        pc++;
    }
    fclose(ptr_myfile);
}