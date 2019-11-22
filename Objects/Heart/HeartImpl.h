#pragma once

#ifndef _OBJ_HEART_IMPL_
#define _OBJ_HEART_IMPL_

#include "Resources.h"
#include "Objects/Heart/HeartIntf.h"

// 체력 값을 change만큼 업데이트하고, 렌더링합니다.
void _Heart_update(Heart *self, float change) {
  self->hp += change;
  self->render(self);
}

// 현재 체력 값에 따라 체력 바 이미지 파일 이름을 반환하는 함수입니다.
char* _Heart_loadResource(Heart *self) {
  int index = (self->hp > 99) ? 20 : (self->hp / 5);
  // 5% 간격으로 이미지를 다르게 표시합니다.
  // 처음에 체력이 바로 닳으면 부자연스러우니까 99 이상이면 100으로 렌더링합니다.

  return RESOURCE_HEART[index];
}

// _Heart_loadResource의 결과로 체력 바에 해당하는 이미지를 업데이트한 뒤, 렌더링합니다.
void _Heart_render(Heart *self) {
  self->image->fileName = _Heart_loadResource(self);
  self->imageLayer->renderAll(self->imageLayer);
}

#endif
