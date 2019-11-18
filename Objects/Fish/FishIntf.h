#pragma once

#ifndef _OBJ_FISH_INTF_
#define _OBJ_FISH_INTF_

#include <Windows.h>
#include "ImageLayer/ImageLayer.h"

typedef struct _Fish {
  int level;
  int x, y;
  int width, height;
  COORD start, end;
  Image *image;
  ImageLayer *imageLayer;

	void (*init)(struct _Fish*);
	void (*update)(struct _Fish*);
  void (*move)(struct _Fish*, int);
} Fish;

#endif
