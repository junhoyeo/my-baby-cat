#pragma once

#ifndef _OBJ_EFFECT_INTF_
#define _OBJ_EFFECT_INTF_

#include "ImageLayer/ImageLayer.h"

typedef struct _Effect {
  Image *image;
  ImageLayer *imageLayer;

  void (*render)(struct _Effect*);
  void (*addBackgroundThread)(struct _Effect*, void (*method)(struct _Effect*));
} Effect;

#endif
