//
// Created by juliu on 11-10-2023.
//

#ifndef RISCVSIM_FILEREADER_H
#define RISCVSIM_FILEREADER_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include "memMan.h"

void readFile(char file[]);
off_t fsize(const char *filename);

#endif //RISCVSIM_FILEREADER_H
