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

 	Image images[2] = {
 		{RESOURCE_CAT[0], 0, 0, 1},
    {RESOURCE_FISH[0], 0, 0, 3},
 	};
 	imageLayer.imageCount = 2;
 	imageLayer.images = images;

  // init cat
  Cat cat = DEFAULT_CAT;
  cat.image = &images[0];
  cat.imageLayer = &imageLayer;
  cat.init(&cat);
  // cat.update(&cat);

  // init fish example; later put to loop
  Fish fish = DEFAULT_FISH;
  fish.image = &images[1];
  fish.imageLayer = &imageLayer;
  fish.x = 1820;
  fish.init(&fish);

  // game start
  imageLayer.renderAll(&imageLayer);

  cat.addBackgroundThread(&cat, cat.run);
  fish.addBackgroundThread(&fish, fish.move);

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
