#pragma once

#ifndef _RESOURCES_
#define _RESOURCES_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* RESOURCE_CAT[8];

inline void updateResources() {
  for (int idx = 1; idx <= 8; idx++) {
    char filename[100];
    sprintf(filename, "resources/cat/cat-p%d.bmp", idx);
    int len = strlen(filename) + 1;
    RESOURCE_CAT[idx - 1] = (char*)malloc(sizeof(char) * len);
    strcpy(RESOURCE_CAT[idx - 1], filename);
  }
}

#endif
