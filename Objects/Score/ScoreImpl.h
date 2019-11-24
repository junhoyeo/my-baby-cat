﻿#pragma once

#ifndef _OBJ_SCORE_IMPL_
#define _OBJ_SCORE_IMPL_

#include <Windows.h>
#include <stdbool.h>
#include "Utils.h"
#include "Objects/Score/ScoreIntf.h"

bool _Score_isFileExists(LPCTSTR szPath) {
  DWORD dwAttrib = GetFileAttributes(szPath);
  return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
        !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

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
  FILE *fp = fopen(filename, "w");
  fprintf(fp, "%d\n", self->score);
  fclose(fp);
}

// filename의 파일로부터 점수를 읽어와 반환합니다.
int _Score_loadHighScore(Score *self, char *filename) {
  if (!_Score_isFileExists((LPCTSTR) filename)) {
    self->save(self, filename);
  }
  int highScore;
  FILE *fp = fopen(filename, "r");
  fscanf(fp, "%d", &highScore);
  fclose(fp);
  return highScore;
}

#endif
