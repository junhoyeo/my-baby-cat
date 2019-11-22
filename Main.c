#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdbool.h>
#include <process.h>
#include <Windows.h>

#include "Init.h"
#include "Utils.h"
// #include "Mouse/Mouse.h"
#include "Keyframe/Keyframe.h"
#include "ImageLayer/ImageLayer.h"

#include "Objects/Cat/Cat.h"
#include "Objects/Fish/Fish.h"
#include "Objects/Obstacle/Obstacle.h"

Fish *(*fishSegmentPointer)[] = NULL;
int _animateFishSegements_current = 0;
bool _animateFishSegments_done = false;

int animateFishSegments(int fishLength) {
  for (int repeat = 0;; repeat++) {
    for (int idx = 0; idx < fishLength; idx++) {
      if (repeat > 10 * idx) {
        if ((*fishSegmentPointer)[idx]->x <= 200) { // 플레이어와 만남
          // TODO: 점프, 슬라이드 시 플레이어가 해당 물고기를 먹을 수 있는지 확인
          Image *image = (*fishSegmentPointer)[idx]->image;
          if (image->isShown) {
            // 살아 있는 물고기면 안 보이게 처리
            image->isShown = false;
            SCORE.update(&SCORE, 100);
          }
        } else { // 이동 가능
          // printf("%d\n", (*fishSegmentPointer)[idx]->x);
          (*fishSegmentPointer)[idx]->move((*fishSegmentPointer)[idx], 10);
          if ((*fishSegmentPointer)[idx]->x <= 1400) {
            _animateFishSegements_current++;
          }
        }
      }
    }
  }
}

int main() {
  initWindow();
  updateResources();
  Sleep(100);

  // Mouse mouse = DEFAULT_MOUSE;

  ImageLayer imageLayer = DEFAULT_IMAGE_LAYER;
 	imageLayer.initialize(&imageLayer);

  Image *images = malloc(9 * sizeof(Image));
  images[0] = (Image) { .fileName = RESOURCE_BACKGROUND[0], .x = 0, .y = 0, .scale = 1, .isShown = true };
  images[1] = (Image) { .fileName = RESOURCE_CAT[0], .x = 0, .y = 450, .scale = 1, .isShown = true };
  imageLayer.imageCount = 2;
  imageLayer.images = images;

  // init cat
  Cat cat = DEFAULT_CAT;
  cat.image = &images[1];
  cat.imageLayer = &imageLayer;
  cat.init(&cat);

  // game start
  imageLayer.renderAll(&imageLayer);

  cat.addBackgroundThread(&cat, cat.run);
  cat.addBackgroundThread(&cat, cat.listenKeys);
  // fish.addBackgroundThread(&fish, fish.move);

  Keyframe *keyframes = createStageOneKeyframes();
  for (int frame = 0; frame < STAGE_ONE_LENGTH; frame++) {
    Keyframe currentFrame = keyframes[frame];
    if (currentFrame.type == KEYFRAME_TYPE_FISH) {
      Fish *fishSegments[5];
      for(int i = 0; i < currentFrame.size; i++) {
        images[i + 2] = (Image) { .fileName = RESOURCE_FISH[0], .x = 2000, .y = 600, .scale = 1, .isShown = true };
        imageLayer.imageCount++;

        fishSegments[i] = malloc(sizeof(Fish));
        *fishSegments[i] = createFish();
        fishSegments[i]->image = &images[i + 2];
        fishSegments[i]->imageLayer = &imageLayer;
        fishSegments[i]->init(fishSegments[i]);
      }
      fishSegmentPointer = &fishSegments;

      _animateFishSegements_current = 0;
      _beginthread(animateFishSegments, 0, (int) currentFrame.size);
      while (_animateFishSegements_current < currentFrame.size) {};
    } else if (currentFrame.type == KEYFRAME_TYPE_OBSTACLE_BOTTOM) {
      Obstacle testObstacle = createObstacleByPos(POSITION_BOTTOM, &imageLayer);
      imageLayer.renderAll(&imageLayer);
    } else if (currentFrame.type == KEYFRAME_TYPE_OBSTACLE_TOP) {
      Obstacle testObstacle = createObstacleByPos(POSITION_TOP, &imageLayer);
      imageLayer.renderAll(&imageLayer);
    }
  }

 	getchar();
}
