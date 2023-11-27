//
// Created by juliu on 11-10-2023.
//

#include "fileReader.h"

void readFile(char file[]){
    uWord fileSize = fsize(file);
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
    while (pc <= fileSize){
        readByte = fgetc(ptr_myfile);
        setByte(readByte,pc);
        pc++;
    }
    setByte(0x00, pc-1);
    fclose(ptr_myfile);
}


off_t fsize(const char *filename) {
    struct stat st;

    if (stat(filename, &st) == 0)
        return st.st_size;

    fprintf(stderr, "Cannot determine size of %s: %s\n",
            filename, strerror(errno));

    return -1;
}