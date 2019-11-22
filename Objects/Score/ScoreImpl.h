#pragma once

#ifndef _OBJ_SCORE_IMPL_
#define _OBJ_SCORE_IMPL_

#include "Utils.h"
#include "Objects/Score/ScoreIntf.h"

void _Score_init(Score *self) {
  return;
}

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

void _Score_save(Score *self, char *filename) {
  return;
}

#endif
