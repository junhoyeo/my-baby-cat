﻿#pragma once

#ifndef _KEYFRAME_
#define _KEYFRAME_

#include <stdlib.h>
#include "Keyframe/KeyframeIntf.h"

// 첫 번째 스테이지의 키프레임을 만듭니다. 각각의 키프레임은 어떤 오브젝트를 몇 개씩 렌더링할지를 정합니다.
Keyframe *createStageOneKeyframes() {
  Keyframe *keyframes = malloc(STAGE_ONE_LENGTH * sizeof(Keyframe));
  keyframes[0] = (Keyframe) {
    .type = KEYFRAME_TYPE_FISH,
    .size = 5,
  };
  keyframes[1] = (Keyframe){
    .type = KEYFRAME_TYPE_OBSTACLE_BOTTOM,
    .size = 1,
  };
  return keyframes;
}

#endif