#pragma once

#ifndef _OBJ_ITEM_INTF_
#define _OBJ_ITEM_INTF_

#define ITEM_TYPE_HEART 0 // 생명 더 주는 아이템
#define ITEM_TYPE_FASTER 1 // 속도 증가 아이템
#define ITEM_TYPE_SLOWER 2 // 속도 감소 아이템
#define ITEM_TYPE_GRACE 3 // 무적 아이템

#include "ImageLayer/ImageLayer.h"

typedef struct _Item {
  int x, y;
  int width, height;
  Image *image;
  ImageLayer *imageLayer;

  void (*init)(struct _Item*);
  void (*update)(struct _Item*);
  void (*move)(struct _Item*, int changeX);
} Item;

#endif
