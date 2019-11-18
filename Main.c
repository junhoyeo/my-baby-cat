#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <Windows.h>
#include "Init.h"
#include "Utils.h"
#include "Mouse/Mouse.h"
#include "Objects/Cat/Cat.h"
#include "ImageLayer/ImageLayer.h"

int main() {
  initWindow();
  updateResources();
  Sleep(100);

  Mouse mouse = DEFAULT_MOUSE;

  ImageLayer imageLayer = DEFAULT_IMAGE_LAYER;
 	imageLayer.initialize(&imageLayer);

 	Image images[1] = {
 		{RESOURCE_CAT[0], 0, 0, 3},
 	};
 	imageLayer.imageCount = 1;
 	imageLayer.images = images;
  imageLayer.renderAll(&imageLayer);

  Cat cat = DEFAULT_CAT;
  cat.image = &images[0];
  cat.imageLayer = &imageLayer;
  cat.init(&cat);
  // cat.update(&cat);

  // 게임 시작
  cat.addBackgroundThread(&cat, cat.run);

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
