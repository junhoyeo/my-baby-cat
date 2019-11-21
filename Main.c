#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdbool.h>
#include <Windows.h>
#include "Init.h"
#include "Utils.h"
#include "Mouse/Mouse.h"
#include "Objects/Cat/Cat.h"
#include "Objects/Fish/Fish.h"
#include "ImageLayer/ImageLayer.h"

int animateFishSegments(Fish *(*fishSegmentPointer)[], int fishLength) {
  int completeCount = 0;
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
        }
      }
    }
  }
}

int main() {
  initWindow();
  updateResources();
  Sleep(100);

  Mouse mouse = DEFAULT_MOUSE;

  ImageLayer imageLayer = DEFAULT_IMAGE_LAYER;
 	imageLayer.initialize(&imageLayer);

 	// Image images[2] = {
 	// 	{RESOURCE_CAT[0], 0, 0, 1},
  //   {RESOURCE_FISH[0], 0, 0, 3},
 	// };
 	// imageLayer.imageCount = 2;
 	// imageLayer.images = images;
  Image *images = malloc(7 * sizeof(Image));
  images[0] = (Image) { .fileName = RESOURCE_BACKGROUND[0], .x = 0, .y = 0, .scale = 1, .isShown = true };
  images[1] = (Image) { .fileName = RESOURCE_CAT[0], .x = 0, .y = 450, .scale = 1, .isShown = true };
  imageLayer.imageCount = 2;
  imageLayer.images = images;

  // init cat
  Cat cat = DEFAULT_CAT;
  cat.image = &images[1];
  cat.imageLayer = &imageLayer;
  cat.init(&cat);
  // cat.update(&cat);

  // init fish example; later put to loop
  // Fish fish = DEFAULT_FISH;
  // fish.image = &images[1];
  // fish.imageLayer = &imageLayer;
  // fish.x = 1820;
  // fish.init(&fish);

  // game start
  imageLayer.renderAll(&imageLayer);

  cat.addBackgroundThread(&cat, cat.run);
  // fish.addBackgroundThread(&fish, fish.move);

  Fish *fishSegments[5];

  for(int i = 0; i < 5; i++) {
    images[i + 2] = (Image) { .fileName = RESOURCE_FISH[0], .x = 2000, .y = 600, .scale = 1, .isShown = true };
    imageLayer.imageCount++;

    // fishSegments[i] = DEFAULT_FISH;
    fishSegments[i] = malloc(sizeof(Fish));
    *fishSegments[i] = (Fish) {
      .level = 0,
      .x = 2000,
      .y = 600,
      .width = 0, .height = 0,
      .isMoving = 0,
      .start = { 0, 0 }, .end = { 0, 0 },
      .image = NULL,
      .imageLayer = NULL,

      .init = _Fish_init,
      .update = _Fish_update,
      .move = _Fish_move,
      // .waitForEnd = _Fish_waitForEnd,
      // .addBackgroundThread = _Fish_addBackgroundThread,
    };
    // printf("%d\n", fishSegments[i]->x);
    fishSegments[i]->image = &images[i + 2];
    fishSegments[i]->imageLayer = &imageLayer;
    fishSegments[i]->init(fishSegments[i]);

    // fishSegments[i].addBackgroundThread(&fishSegments[i], fishSegments[i].move);
    // TODO: merge background listeners to one in global
    // fishSegments를 prop으로 받아서 몇 초 간격으로, 하나씩 돌아가면서 체크하면 될 듯.
    // Sleep(2000);
  }
  cat.jump(&cat);
  // exit(0);

  Fish *(*fishSegmentPointer)[] = &fishSegments;
  int fishSegmentLength = 5;
  animateFishSegments(fishSegmentPointer, 5);
  SCORE.render(&SCORE);

  // while (1) {
  //   // printf("%d\n", mouse.hasInput());
  //   // if (!cat.isRunning) {
  //   //   if (cat.isHovered(&cat, &mouse))
  //   //     cat.addBackgroundThread(&cat, cat.run);
  //   // }
  //   // gotoxy(0, 0);
  //   // printf("");
  // }

  // cat.run(&cat);
 	// getchar();
}
