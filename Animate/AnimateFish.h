#pragma once

#ifndef _ANIMATE_FISH_
#define _ANIMATE_FISH_

#include <Windows.h>
#include "Animate/Animate.h"
#include "Objects/Cat/Cat.h"
#include "Objects/Fish/Fish.h"
#include "ImageLayer/ImageLayer.h"

Fish *(*fishSegmentPointer)[] = NULL;
int _animateFishSegments_received = 0;
int _animateFishSegments_shown = 0;
int _animateFishSegments_finished = 0;
// bool _animateFishSegments_done = false;

void animateFishSegments(AnimateProps* animateProps) {
  Cat *cat = animateProps->cat;
  int fishLength = animateProps->objectLength;
  while (_animateFishSegments_finished < _animateFishSegments_received) {
    for (int idx = 0; idx < fishLength; idx++) {
      Fish *currentFish = (*fishSegmentPointer)[idx];

      if (currentFish->x <= 200) { // 플레이어와 만남
        Image *image = currentFish->image;
        if (image->isShown) {
          // 살아 있는 물고기면 안 보이게 처리
          image->isShown = false;

          if (cat->y >= 400) { // 물고기를 먹었을 때
            // 효과음 재생
            PlaySound(RESOURCE_SOUND_FISH, NULL, SND_FILENAME);
            PlaySound(RESOURCE_SOUND_BGM_1, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

            switch (currentFish->level) {
              case FISH_LEVEL_1:
                SCORE.update(&SCORE, 100);
                break;
              case FISH_LEVEL_2:
                SCORE.update(&SCORE, 120);
                break;
              case FISH_LEVEL_3:
                SCORE.update(&SCORE, 150);
                break;
              case FISH_LEVEL_4:
                SCORE.update(&SCORE, 200);
                break;
              default:
                break;
            }
          }

          _animateFishSegments_finished++;
        }
      } else { // 이동 가능
        // printf("%d\n", currentFish->x);
        currentFish->move(currentFish, 80);
        if (currentFish->x <= 1400) {
          _animateFishSegments_shown++;
        }
      }
    }
    Sleep(SPEED.delay / 1.5);
  }
}

#endif
