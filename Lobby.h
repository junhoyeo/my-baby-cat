#pragma once

#ifndef _LOBBY_
#define _LOBBY_

#include <stdbool.h>
// #include <process.h>
#include "Resources.h"
#include "Mouse/Mouse.h"
#include "ImageLayer/ImageLayer.h"

// 역대 최고 점수와 게임 시작 버튼이 있는 로비 화면을 렌더링합니다.
// showTitle이 true인 경우 로비를 보여주기 전에 타이틀을 표시합니다,.
void renderLobby(ImageLayer* imageLayer, Mouse* mouse, bool showTitle /* = false */) {
  Image *preImages = malloc(8 * sizeof(Image));
  preImages[0] = (Image) { RESOURCE_BACKGROUND_TITLE, -10, -10, 1, .isShown = true };
  preImages[1] = (Image) { RESOURCE_TEXT_START, 670, 880, 0.9, .isShown = true };
  imageLayer->imageCount = 2;
  imageLayer->images = preImages;

  // 타이틀을 표시합니다.
  if (showTitle) {
    imageLayer->renderAll(imageLayer);
    while (1) {
      mouse->updatePosition(mouse);
      // 버튼 위치를 클릭한 경우 타이틀에서 다음 화면으로 넘어갑니다.
      if (mouse->isClicked() && mouse->y >= 400) {
        break;
      }
    }
  }

  // 로비 화면을 표시합니다.
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
  imageLayer->renderAll(imageLayer);

  // 최고 점수를 가져옵니다.
  int score = SCORE.loadHighScore(&SCORE, "data.dat");

  // 최고 점수에 맞게 카운터(각 숫자)를 업데이트하고, 표시합니다.
  int imageIdx = 2;
  while (score != 0) {
    preImages[imageIdx].fileName = RESOURCE_NUMBERS[score % 10];
    // images[imageIdx].x = 1900 - imageIdx * 65,
    score /= 10;
    imageIdx++;
  }
  imageLayer->renderAll(imageLayer);

  while (1) {
    mouse->updatePosition(mouse);

    // 게임 시작 버튼 위치에서 마우스 클릭이 발생했을 경우에만 다음 화면으로 넘어갑니다.
    if (mouse->isClicked() &&
      mouse->x >= 600 && mouse->y >= 200) {
      break;
    }
  }

  // 메모리 할당을 해제합니다.ㄴ
  free(preImages);
}

#endif
