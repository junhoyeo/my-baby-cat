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

#include "Animate/Animate.h"
#include "Animate/AnimateFish.h"
#include "Animate/AnimateItem.h"
#include "Animate/AnimateObstacle.h"

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
