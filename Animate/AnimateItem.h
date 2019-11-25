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

// 백그라운드에서 아이템 세그먼트를 이동시키는 함수입니다.
void animateItemSegments(AnimateProps* animateProps) {
  // 인수로 고양이 객체의 포인터와 아이템 개수, 아이템 타입을 받습니다.
  Cat *cat = animateProps->cat;
  int itemLength = animateProps->objectLength;
  int itemType = animateProps->objectClass;

  // 모든 아이템이 화면에 나타나 사라질 때까지 반복합니다.
  while (_animateItemSegments_finished < _animateItemSegments_received) {
    for (int idx = 0; idx < itemLength; idx++) {
      Item *currentItem = (*ItemSegmentPointer)[idx];

      if (currentItem->x <= 200) { // 플레이어와 만남
        Image *image = currentItem->image;
        if (image->isShown) {
          // 아이템을 안 보이게 처리
          image->isShown = false;

          if (cat->y >= 400) { // 아이템을 먹었을 때
            // 효과음 재생
            PlaySound(RESOURCE_SOUND_ITEM, NULL, SND_FILENAME);
            PlaySound(RESOURCE_SOUND_BGM_1, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

            // TODO: 아이템 타입에 맞게 효과 재생
            switch (itemType) {
              case ITEM_TYPE_LIFE:
                // 체력 회복 아이템
                LIFE.update(&LIFE, 20);
                break;

              case ITEM_TYPE_FASTER:
                // 속도 증가 아이템
                SPEED.addBackgroundThread(&SPEED, SPEED.increase);
                break;

              case ITEM_TYPE_SLOWER:
                // 속도 감소 아에템
                SPEED.addBackgroundThread(&SPEED, SPEED.decrease);
                break;

              default:
                break;
            }


            // 아이템도 젤리니까 점수 줌
            SCORE.update(&SCORE, 80);
          }

          // 화면 밖으로 사라진 아이템의 수를 기록합니다.
          _animateItemSegments_finished++;
        }
      } else { // 이동 가능
        currentItem->move(currentItem, 20);

        // 화면에 보여진 아이템의 수를 기록합니다.
        if (currentItem->x <= 1500) {
          _animateItemSegments_shown++;
        }
      }
    }
    // 전체 딜레이(속도 지표)에 기반하여 일정 시간 동안 딜레이를 줍니다.
    Sleep(SPEED.delay / 1.5);
  }
}

#endif
