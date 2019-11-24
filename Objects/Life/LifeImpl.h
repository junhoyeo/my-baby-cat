#pragma once

#ifndef _OBJ_LIFE_IMPL_
#define _OBJ_LIFE_IMPL_

#include "Resources.h"
#include "Objects/Life/LifeIntf.h"

// 생명 값을 change만큼 업데이트하고, 렌더링합니다.
void _Life_update(Life *self, float change) {
  self->hp += change;
  self->render(self);
}

// 현재 생명 값에 따라 생명 바 이미지 파일 이름을 반환하는 함수입니다.
char* _Life_loadResource(Life *self) {
  int index = (self->hp > 99) ? 20 : (self->hp / 5);
  // 5% 간격으로 이미지를 다르게 표시합니다.
  // 처음에 생명이 바로 닳으면 부자연스러우니까 99 이상이면 100으로 렌더링합니다.

  return RESOURCE_LIFE[index];
}

// _Life_loadResource의 결과로 생명 바에 해당하는 이미지를 업데이트한 뒤, 렌더링합니다.
void _Life_render(Life *self) {
  if (self->image) {
    self->image->fileName = _Life_loadResource(self);
    self->imageLayer->renderAll(self->imageLayer);
  }
}

#endif
