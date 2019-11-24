#pragma once

#ifndef _TITLE_
#define _TITLE_

#include <stdbool.h>
#include <process.h>
#include "Resources.h"
#include "ImageLayer/ImageLayer.h"

typedef struct _AnimateTitleProps {
  Image *image;
  ImageLayer *imageLayer;
} AnimateTitleProps;

bool _Title_isRunning = false;

void animateTitle(AnimateTitleProps *animateTitleProps) {
  _Title_isRunning = true;
  Image *textImage = animateTitleProps->image;
  ImageLayer *imageLayer = animateTitleProps->imageLayer;

  bool first = false;
  while (_Title_isRunning) {
    first = !first;
    Sleep(first ? 300 : 500);
    textImage->x = first ? 640 : 670;
    textImage->scale = first ? 1 : 0.9;
    imageLayer->renderAll(imageLayer);
  }
}

boolean renderTitle() {
  ImageLayer imageLayer = DEFAULT_IMAGE_LAYER;
  imageLayer.initialize(&imageLayer);

  Image images[2] = {
    { RESOURCE_BACKGROUND_TITLE, -10, -10, 1, .isShown = true },
    { RESOURCE_TEXT_START, 670, 880, 0.9, .isShown = true },
  };

  imageLayer.imageCount = 2;
  imageLayer.images = images;
  imageLayer.renderAll(&imageLayer);

  AnimateTitleProps animateTitleProps = (AnimateTitleProps) {
    .image = &images[1],
    .imageLayer = &imageLayer,
  };
  _beginthread(animateTitle, 0, (AnimateTitleProps*) &animateTitleProps);

  Sleep(1000);

  return 1;
}

#endif
