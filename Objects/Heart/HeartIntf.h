#pragma once

#ifndef _OBJ_HEART_INTF_
#define _OBJ_HEART_INTF_

#include "ImageLayer/ImageLayer.h"

typedef struct _Heart {
  float hp;
  Image *image;
  ImageLayer *imageLayer;

  void (*update)(struct _Heart*, float change);
  void (*render)(struct _Heart*);
} Heart;

#endif
