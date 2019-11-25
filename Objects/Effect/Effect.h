#pragma once

#ifndef _OBJ_EFFECT_
#define _OBJ_EFFECT_

#include "ImageLayer/ImageLayer.h"
#include "Keyframe/Keyframe.h"
#include "Objects/Effect/EffectIntf.h"
#include "Objects/Effect/EffectImpl.h"

Effect createEffect(ImageLayer *imageLayer, int obstacleType) {
  Effect newEffect = (Effect) {
    .image = &imageLayer->images[3],
    .imageLayer = imageLayer,
    .render = _Effect_render,
    .addBackgroundThread = _Effect_addBackgroundThread,
  };
  newEffect.image->y = (obstacleType == KEYFRAME_TYPE_OBSTACLE_TOP) ? -150 : -50;
  newEffect.image->y = (obstacleType == KEYFRAME_TYPE_OBSTACLE_TOP) ? 10 : 100;
  return newEffect;
}

#endif
