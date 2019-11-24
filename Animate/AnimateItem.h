#pragma once

#ifndef _ANIMATE_ITEM_
#define _ANIMATE_ITEM_

#include <Windows.h>
#include "Animate/Animate.h"
#include "Objects/Cat/Cat.h"
#include "Objects/Item/Item.h"
#include "ImageLayer/ImageLayer.h"

Item *(*ItemSegmentPointer)[] = NULL;
int _animateItemSegments_received = 0;
int _animateItemSegments_shown = 0;
int _animateItemSegments_finished = 0;

void animateItemSegments(AnimateProps* animateProps) {
  Cat *cat = animateProps->cat;
  int itemLength = animateProps->objectLength;
  while (1) {
    for (int idx = 0; idx < itemLength; idx++) {
      Item *currentItem = (*ItemSegmentPointer)[idx];

      if (currentItem->x <= 200) {
        Image *image = currentItem->image;
        if (image->isShown) {
          image->isShown = false;
          _animateItemSegments_finished++;

          if (cat->y >= 400) { // 아이템을 먹었을 때
            // 효과음 재생
            PlaySound(RESOURCE_SOUND_ITEM, NULL, SND_FILENAME);
            PlaySound(RESOURCE_SOUND_BGM_1, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

            // TODO: 아이템 타입에 맞게 효과 재생

            // 아이템도 젤리니까 점수 줌
            SCORE.update(&SCORE, 80);
          }
        }
      } else { // 이동 가능
        currentItem->move(currentItem, 20);
        if (currentItem->x <= 1500) {
          _animateItemSegments_shown++;
        }
      }
    }
    Sleep(SPEED.delay / 1.5);
  }
}

#endif
