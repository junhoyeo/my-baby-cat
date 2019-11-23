#pragma once

#ifndef _OBJ_SCORE_
#define _OBJ_SCORE_

#include "Objects/Score/ScoreIntf.h"
#include "Objects/Score/ScoreImpl.h"

Score SCORE;

// 점수 오브젝트를 생성합니다.
Score createScore() {
  return (Score) {
    .score = 0, // 사용자 점수
    .images = NULL,
    .imageLayer = NULL,

    .init = _Score_init,
    .update = _Score_update,
    .save = _Score_save,
  };
}

#endif
