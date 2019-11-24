#pragma once

#ifndef _ANIMATE_OBST_
#define _ANIMATE_OBST_

#include <Windows.h>
#include "Animate/Animate.h"
#include "Objects/Cat/Cat.h"
#include "Objects/Effect/Effect.h"
#include "Objects/Obstacle/Obstacle.h"
#include "ImageLayer/ImageLayer.h"

Obstacle *(*ObstacleSegmentPointer)[] = NULL;
int _animateObstacleSegments_received = 0;
int _animateObstacleSegments_shown = 0;
int _animateObstacleSegments_finished = 0;

void animateObstacleSegments(AnimateProps* animateProps) {
  Cat *cat = animateProps->cat;
  int obstacleLength = animateProps->objectLength;
  while (1) {
    for (int idx = 0; idx < obstacleLength; idx++) {
      Obstacle *currentObstacle = (*ObstacleSegmentPointer)[idx];

      if (currentObstacle->x <= 200) { // 플레이어와 만남
        Image *image = currentObstacle->image;
        if (image->isShown) {
          image->isShown = false;

          if (cat->y >= 450) { // 부딪힘
            // 애니메이션 표시
            Effect effect = createEffect(currentObstacle->imageLayer);
            effect.addBackgroundThread(&effect, effect.render);

            // 효과음 재생
            PlaySound(RESOURCE_SOUND_OBST, NULL, SND_FILENAME);
            PlaySound(RESOURCE_SOUND_BGM_1, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

            // 속도 느리게
            SPEED.decrease(&SPEED);

            // 체력 감소
            LIFE.update(&LIFE, -30);

            // 플래그 업데이트
            _animateFishSegments_finished++;
          }
        }
      } else {
        currentObstacle->move(currentObstacle, 20);
        if (currentObstacle->x <= 1500) {
          _animateObstacleSegments_shown++;
        }
      }
      Sleep(SPEED.delay / 1.5);
    }
  }
}

#endif
