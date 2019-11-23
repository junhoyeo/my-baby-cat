#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4819)
#pragma comment(lib, "winmm.lib")
#endif

#include <stdio.h>
#include <stdbool.h>
#include <process.h>
#include <Windows.h>

#include "Init.h"
#include "Utils.h"
#include "Speed.h"
// #include "Mouse/Mouse.h"
#include "Keyframe/Keyframe.h"
#include "ImageLayer/ImageLayer.h"

#include "Objects/Cat/Cat.h"
#include "Objects/Fish/Fish.h"
#include "Objects/Obstacle/Obstacle.h"
#include "Objects/Item/Item.h"

typedef struct _AnimateProps {
  Cat *cat;
  int objectLength;
} AnimateProps;

Fish *(*fishSegmentPointer)[] = NULL;
int _animateFishSegments_shown = 0;
// int _animateFishSegments_finished = 0;
// bool _animateFishSegments_done = false;

void animateFishSegments(AnimateProps* animateProps) {
  Cat *cat = animateProps->cat;
  int fishLength = animateProps->objectLength;
  while (1) {
    for (int idx = 0; idx < fishLength; idx++) {
      if ((*fishSegmentPointer)[idx]->x <= 200) { // 플레이어와 만남
        // TODO: 점프, 슬라이드 시 플레이어가 해당 물고기를 먹을 수 있는지 확인
        Image *image = (*fishSegmentPointer)[idx]->image;
        if (image->isShown) {
          // 살아 있는 물고기면 안 보이게 처리
          image->isShown = false;

          if (cat->y >= 400) {
            SCORE.update(&SCORE, 100);
          }
          // _animateFishSegments_finished++;
        }
      } else { // 이동 가능
        // printf("%d\n", (*fishSegmentPointer)[idx]->x);
        (*fishSegmentPointer)[idx]->move((*fishSegmentPointer)[idx], SPEED.delay / 10);
        if ((*fishSegmentPointer)[idx]->x <= 1400) {
          _animateFishSegments_shown++;
        }
      }
    }
    Sleep(SPEED.delay / 15);
  }
}

Obstacle *(*ObstacleSegmentPointer)[] = NULL;
int _animateObstacleSegments_shown = 0;

void animateObstacleSegments(AnimateProps* animateProps) {
  Cat *cat = animateProps->cat;
  int obstacleLength = animateProps->objectLength;
  while (1) {
    for (int idx = 0; idx < obstacleLength; idx++) {
      Sleep(SPEED.delay / 10);
      (*ObstacleSegmentPointer)[idx]->move((*ObstacleSegmentPointer)[idx], SPEED.delay / 20);
      if ((*ObstacleSegmentPointer)[idx]->x <= 1500) {
        _animateObstacleSegments_shown++;
      }
    }
  }
}

Item *(*ItemSegmentPointer)[] = NULL;
int _animateItemSegments_shown = 0;

void animateItemSegments(AnimateProps* animateProps) {
  Cat *cat = animateProps->cat;
  int itemLength = animateProps->objectLength;
  while (1) {
    for (int idx = 0; idx < itemLength; idx++) {
      Sleep(SPEED.delay / 5);
      (*ItemSegmentPointer)[idx]->move((*ItemSegmentPointer)[idx], SPEED.delay / 20);
      if ((*ItemSegmentPointer)[idx]->x <= 1500) {
        _animateItemSegments_shown++;
      }
    }
  }
}

int main() {
  PlaySound(RESOURCE_SOUND_BGM_1, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
  initWindow();
  updateResources();
  Sleep(100);

  // Mouse mouse = DEFAULT_MOUSE;

  ImageLayer imageLayer = DEFAULT_IMAGE_LAYER;
   imageLayer.initialize(&imageLayer);

  Image *images = malloc(20 * sizeof(Image));
  images[0] = (Image) { .fileName = RESOURCE_BACKGROUND[0], .x = 0, .y = 0, .scale = 1, .isShown = true };
  images[1] = (Image) { .fileName = RESOURCE_CAT[0], .x = 0, .y = 450, .scale = 1, .isShown = true };
  images[2] = (Image) { .fileName = RESOURCE_LIFE[20], .x = 0, .y = 0, .scale = 1, .isShown = true };
  for (int idx = 3; idx < 9; idx++) {
    images[idx] = (Image) {
      .fileName = RESOURCE_NUMBERS[0],
      .x = 2000 - idx * 65,
      .y = 30,
      .scale = 1,
      .isShown = true,
    };
  }
  imageLayer.imageCount = 9;
  imageLayer.images = images;

  // init cat
  Cat cat = DEFAULT_CAT;
  cat.image = &images[1];
  cat.imageLayer = &imageLayer;
  cat.init(&cat);

  // set LIFE
  LIFE.image = &images[2];
  LIFE.imageLayer = &imageLayer;

  // set SCORE
  for (int idx = 3; idx < 9; idx++) {
    SCORE.images[idx - 3] = &images[idx];
    // printf("%s\n", SCORE.images[idx]->fileName);
  }
  SCORE.imageLayer = &imageLayer;
  // exit(0);

  // game start
  imageLayer.renderAll(&imageLayer);

  SPEED.addBackgroundThread(&SPEED, SPEED.init);

  cat.addBackgroundThread(&cat, cat.run);
  cat.addBackgroundThread(&cat, cat.listenKeys);
  // fish.addBackgroundThread(&fish, fish.move);

  Keyframe *keyframes = createStageOneKeyframes();
  for (int frame = 0; frame < STAGE_ONE_LENGTH; frame++) {
    Keyframe currentFrame = keyframes[frame];
    AnimateProps animateProps = (AnimateProps) {
      .cat = &cat,
      .objectLength = currentFrame.size,
    };

    if (currentFrame.type == KEYFRAME_TYPE_FISH) {
      Fish *fishSegments[5];
      for(int i = 0; i < currentFrame.size; i++) {
        images[imageLayer.imageCount] = (Image) { .fileName = RESOURCE_FISH[0], .x = 1900, .y = 600, .scale = 1, .isShown = true };

        fishSegments[i] = malloc(sizeof(Fish));
        *fishSegments[i] = createFish(1900 + i * 200);
        fishSegments[i]->image = &images[imageLayer.imageCount];
        fishSegments[i]->imageLayer = &imageLayer;
        fishSegments[i]->init(fishSegments[i]);
        imageLayer.imageCount++;
      }
      fishSegmentPointer = &fishSegments;

      _animateFishSegments_shown = 0;
      _beginthread(animateFishSegments, 0, (AnimateProps*) &animateProps);
      while (_animateFishSegments_shown < currentFrame.size) {};
    }
    else if (currentFrame.type == KEYFRAME_TYPE_OBSTACLE_BOTTOM) {
      Obstacle *ObstacleSegments[5];
      for(int i = 0; i < currentFrame.size; i++) {
        ObstacleSegments[i] = malloc(sizeof(Obstacle));
        *ObstacleSegments[i] = createObstacleByPos(&imageLayer, POSITION_BOTTOM);
      }
      ObstacleSegmentPointer = &ObstacleSegments;
      _beginthread(animateObstacleSegments, 0, (AnimateProps*) &animateProps);
      while (_animateObstacleSegments_shown < currentFrame.size) {};
    }
    else if (currentFrame.type == KEYFRAME_TYPE_OBSTACLE_TOP) {
      // obstacle = createObstacleByPos(POSITION_T OP, &imageLayer);
      // imageLayer.renderAll(&imageLayer);
    }
    else if (currentFrame.type == KEYFRAME_TYPE_ITEM) {
      Item *ItemSegments[5];
      for (int i = 0; i < currentFrame.size; i++) {
        ItemSegments[i] = malloc(sizeof(Item));
        *ItemSegments[i] = createItemByType(&imageLayer, currentFrame.effect);
      }
      ItemSegmentPointer = &ItemSegments;
      _beginthread(animateItemSegments, 0, (AnimateProps*) &animateProps);
      while (_animateItemSegments_shown < currentFrame.size) {};
    }
  }

  getchar();
}
