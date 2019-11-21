#pragma once

#ifndef _OBJ_CAT_IMPL_
#define _OBJ_CAT_IMPL_

#include <stdbool.h>
#include <process.h>
#include <Windows.h>
#include "Resources.h"
#include "Mouse/Mouse.h"
#include "Objects/Cat/CatIntf.h"

void _Cat_init(Cat* self) {
  const HBITMAP hbitmap = (HBITMAP)LoadImage(NULL, (LPCSTR)RESOURCE_CAT[0], IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	BITMAP bitmap;
	GetObject(hbitmap, sizeof(BITMAP), &bitmap);
	self->width = bitmap.bmWidth;
	self->height = bitmap.bmHeight;
  // TODO: set and use scale as 1
}

void _Cat_update(Cat* self) {
  self->start.X = 0;
	self->start.Y = 0;
	self->end.X = self->x + self->width * 3;
	self->end.Y = self->y + self->height * 3;
}

// int _Cat_isHovered(Cat* self, Mouse* mouse) {
//   mouse->updatePosition(mouse);
//   COORD mousePos = mouse->pos;
//   if (mousePos.X >= self->start.X && mousePos.X <= self->end.X
// 		&& mousePos.Y >= self->start.Y && mousePos.Y <= self->end.Y)
//     return 1;
//   return 0;
// }

// bool loop = true;

// void _Cat_waitForMouse(Cat* self) {
//   Mouse mouse = DEFAULT_MOUSE;
//   while (1) {
//     if (mouse.isClicked() && self->isHovered(self, &mouse)) {
//       // MessageBox(NULL, "wait -> clicked", "", MB_OK);
//       break;
//     }
//   }
//   self->isRunning = 0;
// }

void _Cat_move(Cat* self, int changeX, int changeY) {
  self->x += changeX;
  self->image->x += changeX;

  self->y += changeY;
  self->image->y += changeY;

  self->update(self);
}

void _Cat_run(Cat* self) {
  // _beginthread(*(self->waitForMouse), 0, (Cat*) self);
  int frame = 1;
  while (self->isRunning) {
    self->image->fileName = RESOURCE_CAT[frame];
    // self->move(self, 8, 0);

    self->imageLayer->renderAll(self->imageLayer);
    SCORE.render(&SCORE);
    Sleep(self->delay);

    if (frame > 6) frame = 1;
    else frame++;
  }
  // MessageBox(NULL, "exit", "", MB_OK);
  // self->image->fileName = RESOURCE_CAT[0];
  // self->imageLayer->renderAll(self->imageLayer);
  // SCORE.render(&SCORE);
}

void _Cat_jump(Cat* self) {
  self->isRunning = 0;

  for(int i = 1; i <= 5; i++) {
    self->move(self, 0, -i * 10);
    self->imageLayer->renderAll(self->imageLayer);
    Sleep((5 - i) * 8);
  }

  self->image->fileName = RESOURCE_CAT[8];
  self->imageLayer->renderAll(self->imageLayer);
  Sleep(300);

  for(int i = 5; i >= 1; i--) {
    self->move(self, 0, i * 10);
    self->imageLayer->renderAll(self->imageLayer);
    Sleep((5 - i) * 8);
  }

  // self->image->fileName = RESOURCE_CAT[1];
  // self->imageLayer->renderAll(self->imageLayer);

  self->addBackgroundThread(self, self->run);
}

void _Cat_listenKeys(Cat *self) {
  while (1) {
    if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
      self->addBackgroundThread(self, self->jump);
    }
  }
}

void _Cat_addBackgroundThread(Cat* self, int (*method)(Cat*)) {
  self->isRunning = 1;
  Sleep(200);

  _beginthread(*method, 0, (Cat*) self);
}

#endif
