#pragma once

#ifndef _TITLE_
#define _TITLE_

#include <stdbool.h>
// #include <process.h>
#include "Resources.h"
#include "ImageLayer/ImageLayer.h"

// typedef struct _AnimateTitleProps {
//   Image *image;
//   ImageLayer *imageLayer;
// } AnimateTitleProps;

// bool _Title_isRunning = false;

// void animateTitle(AnimateTitleProps *animateTitleProps) {
//   _Title_isRunning = true;
//   Image *textImage = animateTitleProps->image;
//   ImageLayer *imageLayer = animateTitleProps->imageLayer;

//   bool first = false;
//   while (_Title_isRunning) {
//     first = !first;
//     Sleep(first ? 300 : 500);
//     textImage->x = first ? 640 : 670;
//     textImage->scale = first ? 1 : 0.9;
//     imageLayer->renderAll(imageLayer);
//   }
// }

void renderLobby(ImageLayer* imageLayer, bool showTitle /* = false */) {
  Image *preImages = malloc(8 * sizeof(Image));
  preImages[0] = (Image) { RESOURCE_BACKGROUND_TITLE, -10, -10, 1, .isShown = true };
  preImages[1] = (Image) { RESOURCE_TEXT_START, 670, 880, 0.9, .isShown = true };
  imageLayer->imageCount = 2;
  imageLayer->images = preImages;

  // render title
  if (showTitle) {
    imageLayer->renderAll(imageLayer);
    Sleep(1000);
  }

  // render lobby
  preImages[0].fileName = RESOURCE_BACKGROUND_LOBBY;
  preImages[1].isShown = false;
  for (int idx = 2; idx < 8; idx++) {
    preImages[idx] = (Image) {
      .fileName = RESOURCE_NUMBERS[0],
      .x = 1945 - idx * 60,
      .y = 110,
      .scale = 1,
      .isShown = true,
    };
    imageLayer->imageCount++;
  }
  // exit(0);
  imageLayer->renderAll(imageLayer);
  int score = SCORE.loadHighScore(&SCORE, "data.dat");
  int imageIdx = 2;
  while (score != 0) {
    preImages[imageIdx].fileName = RESOURCE_NUMBERS[score % 10];
    // images[imageIdx].x = 1900 - imageIdx * 65,
    score /= 10;
    imageIdx++;
  }
  imageLayer->renderAll(imageLayer);
  Sleep(3000);

  free(preImages);
}

#endif
