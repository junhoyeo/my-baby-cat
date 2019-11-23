#pragma once

#ifndef _LOBBY_
#define _LOBBY_

#include "Resources.h"
#include "ImageLayer/ImageLayer.h"

void renderLobby() {
  ImageLayer imageLayer = DEFAULT_IMAGE_LAYER;
  imageLayer.initialize(&imageLayer);

  Image images[7] = {
    { RESOURCE_BACKGROUND_LOBBY, -10, -10, 1, .isShown = true },
  };
  for (int idx = 1; idx < 7; idx++) {
    images[idx] = (Image) {
      .fileName = RESOURCE_NUMBERS[0],
      .x = 1900 - idx * 65,
      .y = 110,
      .scale = 1,
      .isShown = true,
    };
  }

  imageLayer.imageCount = 7;
  imageLayer.images = images;
  imageLayer.renderAll(&imageLayer);

  // FIXME: mouse
  if (getchar()) {
    return;
  }
}

#endif
