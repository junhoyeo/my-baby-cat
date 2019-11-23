#pragma once

#ifndef _RESOURCES_
#define _RESOURCES_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RESOURCE_CAT_LEN 10
#define RESOURCE_FISH_LEN 1
#define RESOURCE_BACKGROUND_LEN 1
#define RESOURCE_OBST_TOP_LEN 3
#define RESOURCE_OBST_BOTTOM_LEN 3
#define RESOURCE_LIFE_LEN 21

#define RESOURCE_SOUND_BGM_1 "resources/sound/bgm-1.wav"

char* RESOURCE_CAT[RESOURCE_CAT_LEN];
char* RESOURCE_FISH[RESOURCE_FISH_LEN];
char* RESOURCE_BACKGROUND[RESOURCE_BACKGROUND_LEN];
char* RESOURCE_OBST_TOP[RESOURCE_OBST_TOP_LEN];
char* RESOURCE_OBST_BOTTOM[RESOURCE_OBST_BOTTOM_LEN];
char* RESOURCE_LIFE[RESOURCE_LIFE_LEN];
char* RESOURCE_NUMBERS[10];

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

  char *(*resourceObTopPointer)[] = &RESOURCE_OBST_TOP;
  loadResources(resourceObTopPointer, RESOURCE_OBST_TOP_LEN, "resources/obstacles/top/ob%d.bmp");

  char *(*resourceObBottomPointer)[] = &RESOURCE_OBST_BOTTOM;
  loadResources(resourceObBottomPointer, RESOURCE_OBST_BOTTOM_LEN, "resources/obstacles/bottom/ob%d.bmp");

  char *(*resourceLifePointer)[] = &RESOURCE_LIFE;
  loadResources(resourceLifePointer, RESOURCE_LIFE_LEN, "resources/life/hp%d.bmp");

  char *(*resourceNumbersPointer)[] = &RESOURCE_NUMBERS;
  loadResources(resourceNumbersPointer, 10, "resources/number/%d.bmp");
}

#endif
