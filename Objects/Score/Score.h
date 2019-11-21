#pragma once

#ifndef _OBJ_SCORE_
#define _OBJ_SCORE_

#include "Objects/Score/ScoreIntf.h"
#include "Objects/Score/ScoreImpl.h"

const Score SCORE = {
  0, // score
  0, 0, // x, y

  _Score_init,
  _Score_update,
  _Score_render,
  _Score_save,
};

#endif
