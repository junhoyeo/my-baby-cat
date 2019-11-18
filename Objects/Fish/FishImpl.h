#pragma once

#ifndef _OBJ_FISH_IMPL_
#define _OBJ_FISH_IMPL_

#include <Windows.h>
#include "Resources.h"
#include "Objects/Fish/FishIntf.h"

void _Fish_init(Fish* self) {
  const HBITMAP hbitmap = (HBITMAP)LoadImage(NULL, (LPCSTR)RESOURCE_FISH[self->level], IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	BITMAP bitmap;
	GetObject(hbitmap, sizeof(BITMAP), &bitmap);
	self->width = bitmap.bmWidth;
	self->height = bitmap.bmHeight;
}

void _Fish_update(Fish* self) {
	self->image->x = self->x;
	self->image->y = self->y;
}

void _Fish_move(Fish* self, int changeX) {
	while (1) {
		self->x -= changeX;
		self->update(self);
		self->imageLayer->renderAll(self->imageLayer);
		Sleep(100);
	}
}

#endif
