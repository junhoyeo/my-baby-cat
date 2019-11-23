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

  while (_Title_isRunning) {
    Sleep(300);
    textImage->x = 640;
    textImage->scale = 1;
    imageLayer->renderAll(imageLayer);
    Sleep(500);

    textImage->x = 670;
    textImage->scale = 0.9;
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

  // FIXME: mouse
  if (getchar()) {
    _Title_isRunning = false;
    images[0].fileName = RESOURCE_BACKGROUND_LOBBY;

    return 1;
  }
}

#endif
