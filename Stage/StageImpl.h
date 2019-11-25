#pragma once

#ifndef _STAGE_IMPL_
#define _STAGE_IMPL_

#include <process.h>
#include "Stage/StageIntf.h"

// 사용되지 않는 placeholder 함수입니다.
void _Stage_init(Stage* self) {
  return;
}

// 현재 스테이지 인덱스에 맞는 제목 이미지를 일정 시간 동안 렌더링하고, 숨깁니다.
void _Stage_render(Stage* self) {
  self->image->fileName = RESOURCE_TEXT_STAGE[self->index];
  self->image->isShown = true;
  self->imageLayer->renderAll(self->imageLayer);
  Sleep(3500);
  self->image->isShown = false;
}

// 백그라운드 스레드를 시작합니다.
void _Stage_addBackgroundThread(Stage* self, int (*method)(Stage*)) {
  _beginthread(*method, 0, (Stage*) self);
}

#endif
