#pragma once

#ifndef _OBJ_OBSTACLE_INTF_
#define _OBJ_OBSTACLE_INTF_

#include "ImageLayer/ImageLayer.h"

#define POSITION_BOTTOM 0
#define POSITION_TOP 1

typedef struct _Obstacle {
  int type;
  int position;
  int x, y;
  Image *image;
  ImageLayer *imageLayer;

  void (*init)(struct _Obstacle*, int type, int pos);
  void (*update)(struct _Obstacle*);
  void (*move)(struct _Obstacle*, int changeX);
} Obstacle;

#endif
