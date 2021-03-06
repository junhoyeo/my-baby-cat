﻿#pragma once

#ifndef _OBJ_ITEM_IMPL_
#define _OBJ_ITEM_IMPL_

#include <Windows.h>
#include "Objects/Item/ItemIntf.h"

// Item을 초기화합니다.
void _Item_init(Item *self) {
  char *filename = self->image->fileName;
  const HBITMAP hbitmap = (HBITMAP)LoadImage(NULL, (LPCSTR)filename, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
  BITMAP bitmap;
  GetObject(hbitmap, sizeof(BITMAP), &bitmap);
  int height = bitmap.bmHeight;
  self->y = 650 - height;
  self->update(self);
  self->image->isShown = true;
}

// Item의 렌더링 위치를 업데이트합니다.
void _Item_update(Item *self) {
  self->image->x = self->x;
  self->image->y = self->y;
}

// Item을 changeX만큼 왼쪽으로 이동시킵니다.
void _Item_move(Item *self, int changeX) {
  self->x -= changeX;
  self->update(self);
  self->imageLayer->renderAll(self->imageLayer);
}

#endif
