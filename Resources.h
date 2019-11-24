#pragma once

#ifndef _RESOURCES_
#define _RESOURCES_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RESOURCE_CAT_LEN 10
#define RESOURCE_FISH_LEN 1
#define RESOURCE_BACKGROUND_LEN 5
#define RESOURCE_OBST_TOP_LEN 3
#define RESOURCE_OBST_BOTTOM_LEN 3
#define RESOURCE_LIFE_LEN 21
#define RESOURCE_ITEM_LEN 4
#define RESOURCE_TILE_LEN 1
#define RESOURCE_EFFECT_LEN 10
#define RESOURCE_TEXT_STAGE_LEN 5

#define RESOURCE_SOUND_BGM_1 "resources/sound/bgm-1.wav"
#define RESOURCE_SOUND_FISH "resources/sound/sfx1.wav"
#define RESOURCE_SOUND_ITEM "resources/sound/sfx2.wav"
#define RESOURCE_SOUND_OBST "resources/sound/sfx3.wav"

#define RESOURCE_BACKGROUND_TITLE "resources/background/title.bmp"
#define RESOURCE_BACKGROUND_LOBBY "resources/background/lobby.bmp"
#define RESOURCE_BACKGROUND_RESULT "resources/background/result.bmp"

#define RESOURCE_TEXT_START "resources/text/start.bmp"

char* RESOURCE_CAT[RESOURCE_CAT_LEN];
char* RESOURCE_FISH[RESOURCE_FISH_LEN];
char* RESOURCE_BACKGROUND[RESOURCE_BACKGROUND_LEN];
char* RESOURCE_OBST_TOP[RESOURCE_OBST_TOP_LEN];
char* RESOURCE_OBST_BOTTOM[RESOURCE_OBST_BOTTOM_LEN];
char* RESOURCE_LIFE[RESOURCE_LIFE_LEN];
char* RESOURCE_ITEM[RESOURCE_ITEM_LEN];
char* RESOURCE_TILE[RESOURCE_TILE_LEN];
char* RESOURCE_EFFECT[RESOURCE_EFFECT_LEN];
char* RESOURCE_TEXT_STAGE[RESOURCE_TEXT_STAGE_LEN];
char* RESOURCE_NUMBERS[10];

void loadResources(char *resouceList, int resourceLength, char* formatString) {
  char *(*resourceListPointer)[] = resouceList;
  for (int idx = 1; idx <= resourceLength; idx++) {
    char filename[100];
    sprintf(filename, formatString, idx);
    int len = strlen(filename) + 1;
    (*resourceListPointer)[idx - 1] = (char*)malloc(sizeof(char) * len);
    strcpy((*resourceListPointer)[idx - 1], filename);
  }
}

inline void updateResources() {
  loadResources(&RESOURCE_CAT, RESOURCE_CAT_LEN, "resources/cat/cat-p%d.bmp");
  loadResources(&RESOURCE_FISH, RESOURCE_FISH_LEN, "resources/fish/fish-lv%d.bmp");
  loadResources(&RESOURCE_BACKGROUND, RESOURCE_BACKGROUND_LEN, "resources/background/background-st%d.bmp");
  loadResources(&RESOURCE_OBST_TOP, RESOURCE_OBST_TOP_LEN, "resources/obstacles/top/ob%d.bmp");
  loadResources(&RESOURCE_OBST_BOTTOM, RESOURCE_OBST_BOTTOM_LEN, "resources/obstacles/bottom/ob%d.bmp");
  loadResources(&RESOURCE_LIFE, RESOURCE_LIFE_LEN, "resources/life/hp%d.bmp");
  loadResources(&RESOURCE_ITEM, RESOURCE_ITEM_LEN, "resources/item/item%d.bmp");
  loadResources(&RESOURCE_TILE, RESOURCE_TILE_LEN, "resources/tile/tile%d.bmp");
  loadResources(&RESOURCE_EFFECT, RESOURCE_EFFECT_LEN, "resources/effect/bomb-effect%d.bmp");
  loadResources(&RESOURCE_TEXT_STAGE, RESOURCE_TEXT_STAGE_LEN, "resources/text/stagename%d.bmp");
  loadResources(&RESOURCE_NUMBERS, 10, "resources/number/%d.bmp");
}

#endif
