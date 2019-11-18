#pragma once

#ifndef _OBJ_CAT_INTF_
#define _OBJ_CAT_INTF_

#include <Windows.h>
#include "Mouse/Mouse.h"
#include "ImageLayer/ImageLayer.h"

typedef struct _Cat {
  int x, y;
  int width, height;
  int isRunning;
  float delay;
  COORD start, end;
  Image *image;
  ImageLayer *imageLayer;

	void (*init)(struct Cat*);
	// void (*update)(struct Cat*);
	// int (*isHovered)(struct Cat*, struct Mouse*);
  // void (*waitForMouse)(struct Cat*);
  // void (*move)(struct Cat*, int, int);
	void (*run)(struct Cat*);
  void (*addBackgroundThread)(struct Cat*, int (*method)(struct Cat*));
} Cat;

#endif
