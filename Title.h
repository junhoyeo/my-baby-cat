#pragma once

#ifndef _TITLE_
#define _TITLE_

#include <stdbool.h>
#include "Resources.h"
#include "ImageLayer/ImageLayer.h"

boolean renderTitle() {
  ImageLayer imageLayer = DEFAULT_IMAGE_LAYER;
  imageLayer.initialize(&imageLayer);

  Image images[3] = {
    { RESOURCE_BACKGROUND_TITLE, -10, -10, 1, .isShown = true },
  };

  imageLayer.imageCount = 1;
  imageLayer.images = images;
  imageLayer.renderAll(&imageLayer);

  while (1) {};
  return 1;
}

#endif
