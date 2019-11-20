#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <Windows.h>
#include "Init.h"
#include "Utils.h"
#include "Mouse/Mouse.h"
#include "Objects/Cat/Cat.h"
#include "Objects/Fish/Fish.h"
#include "ImageLayer/ImageLayer.h"

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
  Image *images = malloc(6 * sizeof(Image));
  images[0] = (Image) { .fileName = RESOURCE_CAT[0], .x = 0, .y = 0, .scale = 1 };
  imageLayer.imageCount = 1;
  imageLayer.images = images;

  // init cat
  Cat cat = DEFAULT_CAT;
  cat.image = &images[0];
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

  Fish *fishSegments = malloc(5 * sizeof(Fish));
  // images = malloc(6 * sizeof(Image));

  for(int i = 0; i < 5; i++) {
    images[i + 1] = (Image) { .fileName = RESOURCE_FISH[0], .x = 0, .y = 0, .scale = 3 };
    imageLayer.imageCount++;

    fishSegments[i] = DEFAULT_FISH;
    fishSegments[i].image = &images[1 + i];
    fishSegments[i].imageLayer = &imageLayer;
    fishSegments[i].x = 1820;
    fishSegments[i].init(&fishSegments[i]);

    fishSegments[i].addBackgroundThread(&fishSegments[i], fishSegments[i].move);
    Sleep(2000);
  }

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
 	getchar();
}
