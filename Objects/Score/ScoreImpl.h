#pragma once

#ifndef _OBJ_SCORE_IMPL_
#define _OBJ_SCORE_IMPL_

#include "Utils.h"
#include "Objects/Score/ScoreIntf.h"

// 실제로 사용되지 않는 더미 함수입니다.
void _Score_init(Score *self) {
  return;
}

/*
  점수를 change만큼 업데이트해서 렌더링합니다.
  SelectObject를 이용할 생각을 하지 못했기 때문에 6자리 자릿수에 따른 각각의 이미지를 사용해
  커스텀 폰트로 점수를 렌더링하는 방법을 사용했습니다.
*/
void _Score_update(Score *self, int change) {
  self->score += change;
  int number = self->score;
  int imageIdx = 0;
  while (number != 0) {
    self->images[imageIdx]->fileName = RESOURCE_NUMBERS[number % 10];
    number /= 10;
    imageIdx++;
  }
}

// filename의 파일로부터 점수를 저장합니다.
void _Score_save(Score *self, char *filename) {
  return;
}

// filename의 파일로부터 점수를 불러옵니다.
void _Score_load(Score *self, char *filename) {
  return;
}

#endif
