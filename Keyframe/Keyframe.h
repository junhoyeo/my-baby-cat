#pragma once

#ifndef _KEYFRAME_
#define _KEYFRAME_

#include <stdlib.h>
#include "Keyframe/KeyframeIntf.h"

Keyframe *createStageOneKeyframes() {
  Keyframe *keyframes = malloc(STAGE_ONE_LENGTH * sizeof(Keyframe));
  keyframes[1] = (Keyframe) {
    .type = KEYFRAME_TYPE_FISH,
    .size = 5,
  };
  keyframes[0] = (Keyframe){
    .type = KEYFRAME_TYPE_OBSTACLE_BOTTOM,
    .size = 1,
  };
  return keyframes;
}

#endif
