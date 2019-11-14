#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <Windows.h>
#include "Init.h"
#include "Utils.h"
#include "Resources.h"
#include "ImageLayer/ImageLayer.h"

int main() {
  initWindow();
  updateResources();
  Sleep(100);

  ImageLayer imageLayer = DEFAULT_IMAGE_LAYER;
 	imageLayer.initialize(&imageLayer);

 	Image images[1] = {
 		{CAT[0], 0, 0, 3},
 	};
 	imageLayer.imageCount = 1;
 	imageLayer.images = images;
  imageLayer.renderAll(&imageLayer);

  int frame = 2;
  while (1) {
    images[0].fileName = CAT[frame];
    imageLayer.renderAll(&imageLayer);

    Sleep(100);
    frame = (frame > 6) ? 2 : frame + 1;
  }
 	getchar();
}
