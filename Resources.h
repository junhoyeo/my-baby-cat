#pragma once

#ifndef _RESOURCES_
#define _RESOURCES_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RESOURCE_CAT_LEN 10
#define RESOURCE_FISH_LEN 1
#define RESOURCE_BACKGROUND_LEN 1

char* RESOURCE_CAT[RESOURCE_CAT_LEN];
char* RESOURCE_FISH[RESOURCE_FISH_LEN];
char* RESOURCE_BACKGROUND[RESOURCE_BACKGROUND_LEN];

void loadResources(char *(*resourceListPointer)[], int resourceLength, char* formatString) {
  for (int idx = 1; idx <= resourceLength; idx++) {
    char filename[100];
    sprintf(filename, formatString, idx);
    int len = strlen(filename) + 1;
    (*resourceListPointer)[idx - 1] = (char*)malloc(sizeof(char) * len);
    strcpy((*resourceListPointer)[idx - 1], filename);
  }
}

inline void updateResources() {
  char *(*resourceCatPointer)[] = &RESOURCE_CAT;
  loadResources(resourceCatPointer, RESOURCE_CAT_LEN, "resources/cat/cat-p%d.bmp");

  char *(*resourceFishPointer)[] = &RESOURCE_FISH;
  loadResources(resourceFishPointer, RESOURCE_FISH_LEN, "resources/fish/fish-lv%d.bmp");

  char *(*resourceBgPointer)[] = &RESOURCE_BACKGROUND;
  loadResources(resourceBgPointer, RESOURCE_BACKGROUND_LEN, "resources/background/background-st%d.bmp");
}

#endif
