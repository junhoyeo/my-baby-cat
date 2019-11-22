#pragma once

#ifndef _OBJ_FISH_IMPL_
#define _OBJ_FISH_IMPL_

#include <Windows.h>
#include "Resources.h"
#include "Objects/Fish/FishIntf.h"

// 물고기 객체를 초기화합니다. 추후 위치 조정에 사용할 수 있도록 비트맵의 높이와 넓이를 구해 저장합니다.
void _Fish_init(Fish* self) {
  const HBITMAP hbitmap = (HBITMAP)LoadImage(NULL, (LPCSTR)RESOURCE_FISH[self->level], IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	BITMAP bitmap;
	GetObject(hbitmap, sizeof(BITMAP), &bitmap);
	self->width = bitmap.bmWidth;
	self->height = bitmap.bmHeight;
	self->update(self);
}

// 물고기의 x, y 속성에 따라 물고기 이미지의 위치를 업데이트합니다.
void _Fish_update(Fish* self) {
	self->image->x = self->x;
	self->image->y = self->y;
}

// void _Fish_waitForEnd(Fish* self) {
//   while (1) {
//     if (self->x < 100)
//       break;
//   }
//   self->isMoving = 0;
// }

// 물고기를 changeX만큼 왼쪽으로 이동시키고, 렌더링합니다.
void _Fish_move(Fish* self, int changeX) {
	self->x -= changeX;
	self->update(self);
	self->imageLayer->renderAll(self->imageLayer);

	// TODO: delete or hide fish here
}

// void _Fish_addBackgroundThread(Fish* self, int (*method)(Fish*)) {
// 	self->isMoving = 1;
//   _beginthread(*method, 0, (Fish*) self);
// }

#endif
