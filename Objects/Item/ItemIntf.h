#pragma once

#ifndef _OBJ_ITEM_INTF_
#define _OBJ_ITEM_INTF_

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
