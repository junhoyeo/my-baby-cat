#pragma once

#ifndef _LOBBY_
#define _LOBBY_

#include "Resources.h"
#include "ImageLayer/ImageLayer.h"
#include "Objects/Score/Score.h"

void renderLobby() {
  ImageLayer imageLayer = DEFAULT_IMAGE_LAYER;
  imageLayer.initialize(&imageLayer);

  Image images[7] = {
    { RESOURCE_BACKGROUND_LOBBY, -10, -10, 1, .isShown = true },
    { NULL, 0, 0, 1, .isShown = false },
  };
  for (int idx = 2; idx < 8; idx++) {
    images[idx] = (Image) {
      .fileName = RESOURCE_NUMBERS[0],
      .x = 1900 - idx * 65,
      .y = 110,
      .scale = 1,
      .isShown = true,
    };
  }

  imageLayer.imageCount = 8;
  imageLayer.images = images;
  imageLayer.renderAll(&imageLayer);
  Sleep(500);

  int score = SCORE.loadHighScore(&SCORE, "data.dat");
  int imageIdx = 2;
  while (score != 0) {
    images[imageIdx].fileName = RESOURCE_NUMBERS[score % 10];
    // images[imageIdx].x = 1900 - imageIdx * 65,
    score /= 10;
    imageIdx++;
  }
  imageLayer.renderAll(&imageLayer);

  // FIXME: mouse
  // Sleep(500);
  if (getchar()) {
    return;
  }
  // Sleep(1000);
}

#endif
