#pragma once

#ifndef _OBJ_OBSTACLE_IMPL_
#define _OBJ_OBSTACLE_IMPL_

#include <stdbool.h>
#include <Windows.h>
#include "Objects/Obstacle/ObstacleIntf.h"

void _Obstacle_init(Obstacle *self, int type, int pos) {
  const HBITMAP hbitmap = (HBITMAP)LoadImage(NULL, (LPCSTR)self->image->fileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	BITMAP bitmap;
	GetObject(hbitmap, sizeof(BITMAP), &bitmap);
	int height = bitmap.bmHeight;

  self->type = type;
  self->position = pos;
  self->x = 1000;
  self->y = 620 - height;
  self->update(self);
  self->image->isShown = true;
}

void _Obstacle_update(Obstacle *self) {
  self->image->x = self->x;
  self->image->y = self->y;
}

void _Obstacle_move(Obstacle *self, int changeX) {
  self->x -= changeX;
  self->update(self);
  self->imageLayer->renderAll(self->imageLayer);

  SCORE.render(&SCORE);
}

#endif
