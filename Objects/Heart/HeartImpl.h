#pragma once

#ifndef _OBJ_HEART_IMPL_
#define _OBJ_HEART_IMPL_

#include "Resources.h"
#include "Objects/Heart/HeartIntf.h"

void _Heart_update(Heart *self, float change) {
  self->hp += change;
  self->render(self);
}

char* _Heart_loadResource(Heart *self) {
  int index = (self->hp > 99) ? 20 : (self->hp / 5);
  // 5% 간격으로 이미지를 다르게 표시한다.
  // 처음에 체력이 바로 닳으면 부자연스러우니까 99 이상이면 100으로 렌더링한다.

  return RESOURCE_HEART[index];
}

void _Heart_render(Heart *self) {
  self->image->fileName = _Heart_loadResource(self);
  self->imageLayer->renderAll(self->imageLayer);
}

#endif
