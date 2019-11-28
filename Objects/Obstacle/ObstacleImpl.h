#pragma once

#ifndef _OBJ_OBSTACLE_IMPL_
#define _OBJ_OBSTACLE_IMPL_

#include <stdbool.h>
#include <Windows.h>
#include "Utils.h"
#include "Objects/Obstacle/ObstacleIntf.h"

// 장애물을 초기화합니다. 인수로 받은 장애물 위치와 비트맵을 통해 구한 높이에 따라 시작 위치를 조정합니다.
void _Obstacle_init(Obstacle *self, int pos) {
  const HBITMAP hbitmap = (HBITMAP)LoadImage(NULL, (LPCSTR)self->image->fileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
  BITMAP bitmap;
  GetObject(hbitmap, sizeof(BITMAP), &bitmap);
  int height = bitmap.bmHeight;

  self->position = pos;
  self->y = (!pos) ? 550 - height : 150;
  self->update(self);
  self->image->isShown = true;
}

// 장애물의 x, y 속성에 따라 장애물 이미지의 위치를 업데이트합니다.
void _Obstacle_update(Obstacle *self) {
  self->image->x = self->x;
  self->image->y = self->y;
}

// 장애물을 왼쪽으로 changeX만큼 이동시키고 렌더링합니다.
void _Obstacle_move(Obstacle *self, int changeX) {
  self->x -= changeX;
  self->update(self);
  self->imageLayer->renderAll(self->imageLayer);
}

#endif
