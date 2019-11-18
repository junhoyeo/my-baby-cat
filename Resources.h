#pragma once

#ifndef _RESOURCES_
#define _RESOURCES_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RESOURCE_CAT_LEN 8
#define RESOURCE_FISH_LEN 1

char* RESOURCE_CAT[RESOURCE_CAT_LEN];
char* RESOURCE_FISH[RESOURCE_FISH_LEN];

inline void updateResources() {
  // TODO: Abstraction needed!!!

  // export cat resources to array automatically
  for (int idx = 1; idx <= RESOURCE_CAT_LEN; idx++) {
    char filename[100];
    sprintf(filename, "resources/cat/cat-p%d.bmp", idx);
    int len = strlen(filename) + 1;
    RESOURCE_CAT[idx - 1] = (char*)malloc(sizeof(char) * len);
    strcpy(RESOURCE_CAT[idx - 1], filename);
  }

  // export fish resources to array automatically
  for (int idx = 1; idx <= RESOURCE_FISH_LEN; idx++) {
    char filename[100];
    sprintf(filename, "resources/fish/fish-lv%d.bmp", idx);
    int len = strlen(filename) + 1;
    RESOURCE_FISH[idx - 1] = (char*)malloc(sizeof(char) * len);
    strcpy(RESOURCE_FISH[idx - 1], filename);
  }
}

#endif
