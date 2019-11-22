#pragma once

#ifndef _OBJ_LIFE_INTF_
#define _OBJ_LIFE_INTF_

#include "ImageLayer/ImageLayer.h"

typedef struct _Life {
  float hp;
  Image *image;
  ImageLayer *imageLayer;

  void (*update)(struct _Life*, float change);
  void (*render)(struct _Life*);
} Life;

#endif
