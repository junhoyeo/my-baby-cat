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

// 백그라운드에서 물고기 세그먼트를 이동시키는 함수입니다.
void animateFishSegments(AnimateProps* animateProps) {
  // 인수로 고양이 객체의 포인터와 물고기 떼의 길이를 받습니다.
  Cat *cat = animateProps->cat;
  int fishLength = animateProps->objectLength;

  // 모든 물고기가 화면에 나타나 사라질 때까지 반복합니다.
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

            // 물고기의 레벨에 맞는 점수를 지급합니다.
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

          // 화면 밖으로 사라진 물고기의 수를 기록합니다.
          _animateFishSegments_finished++;
        }
      } else { // 이동 가능
        currentFish->move(currentFish, 80);

        // 화면에 보여진 물고기의 수를 기록합니다.
        if (currentFish->x <= 1400) {
          _animateFishSegments_shown++;
        }
      }
    }
    // 전체 딜레이(속도 지표)에 기반하여 일정 시간 동안 딜레이를 줍니다.
    Sleep(SPEED.delay / 1.5);
  }
}

#endif
