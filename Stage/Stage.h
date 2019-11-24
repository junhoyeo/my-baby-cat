#pragma once

#ifndef _STAGE_
#define _STAGE_

#include <stdlib.h>
#include "Keyframe/Keyframe.h"
#include "ImageLayer/ImageLayer.h"

#include "Stage/StageIntf.h"
#include "Stage/StageImpl.h"
#include "Stage/StageFrames.h"

Stage *createStages(ImageLayer *imageLayer, Image *image) {
  Stage *stages[5];
  for (int idx = 0; idx < 5; idx++) {
    stages[idx] = malloc(sizeof(Stage));
    *stages[idx] = (Stage) {
      .keyframes = NULL,
      .length = 0,
      .image = image,
      .imageLayer = imageLayer,
      .init = _Stage_init,
      .render = _Stage_render,
      .update = NULL,
      .addBackgroundThread = _Stage_addBackgroundThread,
    };
  }

  stages[0]->update = _Stage_createStageOneKeyframes;
  stages[1]->update = _Stage_createStageTwoKeyframes;
  stages[2]->update = _Stage_createStageThreeKeyframes;
  stages[3]->update = _Stage_createStageFourKeyframes;
  stages[4]->update = _Stage_createStageFiveKeyframes;

  for (int i = 0; i < 5; i++) {
    stages[i]->update(stages[i]);
  }
  return stages;
}

#endif
