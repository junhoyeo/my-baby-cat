#pragma once

#ifndef _RENDERER_
#define _RENDERER_

#include "Objects/Fish/Fish.h"
#include "Objects/Obstacle/Obstacle.h"

#define KEYFRAME_TYPE_FISH 0
#define KEYFRAME_TYPE_OBSTACLE_BOTTOM 1
#define KEYFRAME_TYPE_OBSTACLE_TOP 2
#define STAGE_ONE_LENGTH 2

typedef struct _Keyframe {
  int type;
  int size;
} Keyframe;

Keyframe *createStageOneKeyframe() {
  Keyframe *keyframes = malloc(STAGE_ONE_LENGTH * sizeof(Keyframe));
  keyframes[0] = {
    .type = KEYFRAME_TYPE_FISH,
    .size = 5,
  };
  keyframes[1] = {
    .type = KEYFRAME_TYPE_OBSTACLE_BOTTOM,
    .size = 1,
  }
  return keyframes;
}

#endif
