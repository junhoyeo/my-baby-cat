#pragma once

#ifndef _OBJ_ITEM_IMPL_
#define _OBJ_ITEM_IMPL_

void _Item_init(Item *self) {
  char *filename = self->image->fileName;
  const HBITMAP hbitmap = (HBITMAP)LoadImage(NULL, (LPCSTR)filename, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
  BITMAP bitmap;
  GetObject(hbitmap, sizeof(BITMAP), &bitmap);
  self->width = bitmap.bmWidth;
  self->height = bitmap.bmHeight;
  // self->update(self);
}

void _Item_update(Item *self) {
  self->image->x = self->x;
  self->image->y = self->y;
}

void _Item_move(Item *self, int changeX) {
  self->x -= changeX;
  self->update(self);
  self->imageLayer->renderAll(self->imageLayer);
}

#endif
