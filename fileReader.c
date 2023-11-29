//
// Created by juliu on 11-10-2023.
//

#include "fileReader.h"
/**
 * reads fil given as file in to memory
 * @param file
 * Note no catch for files larger then 1 MiB
 */
void readFile(char file[]){
    uWord fileSize = fsize(file);// gets size og file
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
    while (pc <= fileSize){//transfer 1 byte per cycle
        readByte = fgetc(ptr_myfile);
        setByte(readByte,pc);
        pc++;
    }
    setByte(0x00, pc-1);
    fclose(ptr_myfile);//always close hte f**king file
}

/**
 * gets size of a file
 * @param filename
 * @return file size
 */
off_t fsize(const char *filename) {
    struct stat st;

    if (stat(filename, &st) == 0)
        return st.st_size;

    fprintf(stderr, "Cannot determine size of %s: %s\n",
            filename, strerror(errno));

    return -1;
}