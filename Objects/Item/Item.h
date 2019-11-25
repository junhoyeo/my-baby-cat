#pragma once

#ifndef _OBJ_ITEM_
#define _OBJ_ITEM_

#include <stdbool.h>
#include "Resources.h"
#include "Objects/Item/ItemIntf.h"
#include "Objects/Item/ItemImpl.h"

const Item DEFAULT_ITEM = {
  .x = 2000,
  .y = 500,
  .image = NULL,
  .imageLayer = NULL,

  .init = _Item_init,
  .update = _Item_update,
  .move = _Item_move,
};

// type에 맞는 새로운 Item 객체를 반환합니다.
Item createItemByType(ImageLayer* imageLayer, int type) {
  Item newItem = DEFAULT_ITEM;
  imageLayer->imageCount++;
  Image *images = imageLayer->images;
  int imageIndex = imageLayer->imageCount - 1;

  images[imageIndex] = (Image){
    .fileName = RESOURCE_ITEM[type],
    .x = 0,
    .y = 0,
    .scale = 1,
    .isShown = false,
  };
  // imageLayer->imageCount++;

  newItem.image = &images[imageIndex];
  newItem.imageLayer = imageLayer;
  newItem.init(&newItem);
  return newItem;
}

#endif
