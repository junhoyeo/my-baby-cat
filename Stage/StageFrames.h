﻿#pragma once

#ifndef _STAGE_FRAMES_
#define _STAGE_FRAMES_

#include <stdlib.h>
#include "Keyframe/Keyframe.h"
#include "Stage/StageIntf.h"

void _Stage_createStageOneKeyframes(Stage *self) {
  int STAGE_ONE_LENGTH = 3;
  Keyframe *keyframes = malloc(STAGE_ONE_LENGTH * sizeof(Keyframe));
  keyframes[2] = (Keyframe) {
    .type = KEYFRAME_TYPE_ITEM,
    .effect = ITEM_TYPE_LIFE,
    .size = 1,
  };
  keyframes[1] = (Keyframe) {
    .type = KEYFRAME_TYPE_FISH,
    .effect = NULL,
    .size = 5,
  };
  keyframes[0] = (Keyframe){
    .type = KEYFRAME_TYPE_OBSTACLE_BOTTOM,
    .effect = NULL,
    .size = 1,
  };
  self->keyframes = keyframes;
  self->length = STAGE_ONE_LENGTH;
}

void _Stage_createStageTwoKeyframes(Stage *self) {
  return;
}

void _Stage_createStageThreeKeyframes(Stage *self) {
  return;
}

void _Stage_createStageFourKeyframes(Stage *self) {
  return;
}

void _Stage_createStageFiveKeyframes(Stage *self) {
  return;
}

#endif
