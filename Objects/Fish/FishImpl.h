#pragma once

#ifndef _OBJ_FISH_IMPL_
#define _OBJ_FISH_IMPL_

#include <Windows.h>
#include "Utils.h"
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

// 물고기를 changeX만큼 왼쪽으로 이동시키고, 렌더링합니다.
void _Fish_move(Fish* self, int changeX) {
  self->x -= changeX;
  self->update(self);
  self->imageLayer->renderAll(self->imageLayer);

  // TODO: delete or hide fish here
}

// 물고기를 랜덤 레벨로 설정합니다.
void _Fish_updateRandomLevel(Fish* self) {
  int rnd = randrange(100);
  if (rnd < 70) { // 레벨 1
    self->level = FISH_LEVEL_1;
    self->image->fileName = RESOURCE_FISH[0];
  } else if (rnd < 85) { // 레벨 2
    self->level = FISH_LEVEL_2;
    self->image->fileName = RESOURCE_FISH[1];
  } else if (rnd < 95) { // 레벨 3
    self->level = FISH_LEVEL_3;
    self->image->fileName = RESOURCE_FISH[2];
  } else { // 레벨 3
    self->level = FISH_LEVEL_4;
    self->image->fileName = RESOURCE_FISH[3];
  }
}

#endif
