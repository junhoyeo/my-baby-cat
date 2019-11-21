#pragma once

#ifndef _OBJ_SCORE_IMPL_
#define _OBJ_SCORE_IMPL_

#include "Utils.h"
#include "Objects/Score/ScoreIntf.h"

void _Score_init(Score *self) {
  return;
}

void _Score_render(Score *self) {
  gotoxy(self->x, self->y);
  printf("score: %d", self->score);
  return;
}

void _Score_update(Score *self, int change) {
  self->score += change;
  self->render(self);
  return;
}

void _Score_save(Score *self, char *filename) {
  return;
}

#endif
