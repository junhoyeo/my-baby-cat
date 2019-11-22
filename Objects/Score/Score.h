#pragma once

#ifndef _OBJ_SCORE_
#define _OBJ_SCORE_

#include "Objects/Score/ScoreIntf.h"
#include "Objects/Score/ScoreImpl.h"

Score SCORE;

Score createScore() {
  return (Score) {
    .score = 0,
    .x = 0,
    .y = 0,

    .init = _Score_init,
    .update = _Score_update,
    .render = _Score_render,
    .save = _Score_save,
  };
}

#endif
