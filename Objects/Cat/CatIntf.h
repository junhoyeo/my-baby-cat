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

	void (*init)(struct _Cat*);
	// void (*update)(struct _Cat*);
	// int (*isHovered)(struct _Cat*, struct Mouse*);
  // void (*waitForMouse)(struct _Cat*);
  void (*move)(struct _Cat*, int, int);
	void (*run)(struct _Cat*);
  void (*jump)(struct _Cat*);
  void (*slide)(struct _Cat*);
  void (*listenKeys)(struct _Cat);
  void (*addBackgroundThread)(struct _Cat*, void (*method)(struct _Cat*));
} Cat;

#endif
