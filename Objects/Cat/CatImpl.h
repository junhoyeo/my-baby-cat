#pragma once

#ifndef _OBJ_CAT_IMPL_
#define _OBJ_CAT_IMPL_

#include <stdbool.h>
#include <process.h>
#include <Windows.h>
#include "Resources.h"
// #include "Mouse/Mouse.h"
#include "Objects/Life/Life.h"
#include "Objects/Score/Score.h"
#include "Objects/Cat/CatIntf.h"

// 고양이 객체를 초기화합니다. 렌더링 시 위치 조절에 사용될 수 있도록 이미지의 height, width를 얻어 저장합니다.
void _Cat_init(Cat* self) {
  const HBITMAP hbitmap = (HBITMAP)LoadImage(NULL, (LPCSTR)RESOURCE_CAT[0], IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
  BITMAP bitmap;
  GetObject(hbitmap, sizeof(BITMAP), &bitmap);
  self->width = bitmap.bmWidth;
  self->height = bitmap.bmHeight;
}

// 아래는 사용되지 않는 코드입니다.
// TODO: set and use scale as 1

// void _Cat_update(Cat* self) {
//   self->start.X = 0;
//   self->start.Y = 0;
//   self->end.X = self->x + self->width * 3;
//   self->end.Y = self->y + self->height * 3;
// }

// int _Cat_isHovered(Cat* self, Mouse* mouse) {
//   mouse->updatePosition(mouse);
//   COORD mousePos = mouse->pos;
//   if (mousePos.X >= self->start.X && mousePos.X <= self->end.X
//     && mousePos.Y >= self->start.Y && mousePos.Y <= self->end.Y)
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

// 고양이 객체를 changeX, changeY만큼 움직입니다.
void _Cat_move(Cat* self, int changeX, int changeY) {
  self->x += changeX;
  self->image->x += changeX;

  self->y += changeY;
  self->image->y += changeY;

  // self->update(self);
}

// 고양이를 달리게 합니다. self->isRunning이 설정되어 있는 한 계속 돌아갑니다.
void _Cat_run(Cat* self) {
  // _beginthread(*(self->waitForMouse), 0, (Cat*) self);
  int frame = 1;
  while (self->isRunning) {
    self->image->fileName = RESOURCE_CAT[frame];
    // self->move(self, 8, 0);

    self->imageLayer->renderAll(self->imageLayer);

    LIFE.update(&LIFE, -0.025);
    // 달리는 도중에 생명이 미세하게 줄어든다.

    Sleep(self->delay);

    if (frame > 6) frame = 1;
    else frame++;
  }
  // MessageBox(NULL, "exit", "", MB_OK);
  // self->image->fileName = RESOURCE_CAT[0];
  // self->imageLayer->renderAll(self->imageLayer);
}

// 고양이가 점프하게 합니다.
void _Cat_jump(Cat* self) {
  // 달리고 있다면 중단시킵니다.
  self->isRunning = 0;

  // 위치 변경에 따라 적당한 딜레이를 주어 더 자연드럽게 보이게 합니다.
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

  // 점프 후 쓰레드를 다시 시작해 다시 달리게 합니다.
  self->addBackgroundThread(self, self->run);
}

// 고양이를 슬라이딩하게 합니다.
void _Cat_slide(Cat *self) {
  self->isRunning = 0;
  self->image->fileName = RESOURCE_CAT[9];
  self->imageLayer->renderAll(self->imageLayer);
}

// 백그라운드에서 실행되며 키 입력을 감지하는 함수입니다.
void _Cat_listenKeys(Cat *self) {
  while (1) {
    if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
      // 스페이스 키가 입력된다면 점프합니다.
      self->addBackgroundThread(self, self->jump);
    } else if (GetAsyncKeyState(VK_DOWN) & 0x8001) {
      // 슬라이드 키를 누르고 있는 동안 슬라이딩합니다.
      self->slide(self);
      Sleep(150);
      self->addBackgroundThread(self, self->run);
    }
  }
}

// 백그라운드 쓰레드를 시작합니다.
void _Cat_addBackgroundThread(Cat* self, int (*method)(Cat*)) {
  self->isRunning = 1;
  Sleep(200);

  _beginthread(*method, 0, (Cat*) self);
}

#endif
