#pragma once

#ifndef _OBJ_HEART_INTF_
#define _OBJ_HEART_INTF_

#include "ImageLayer/ImageLayer.h"

typedef struct _Heart {
  int hp;
  Image *image;
  ImageLayer *imageLayer;

  void (*update)(struct _Heart, int change);
  void (*render)(struct _Heart);
} Heart;

#endif
