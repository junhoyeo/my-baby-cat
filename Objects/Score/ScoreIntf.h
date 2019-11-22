#pragma once

#ifndef _OBJ_SCORE_INTF_
#define _OBJ_SCORE_INTF_

#include "ImageLayer/ImageLayer.h"

typedef struct _Score {
  int score;

  Image *images[6];
  ImageLayer *imageLayer;

  void (*init)(struct _Score*);
  void (*update)(struct _Score*, int);
  void (*save)(struct _Score*, char*);
} Score;

#endif
