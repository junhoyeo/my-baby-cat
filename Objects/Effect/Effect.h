#pragma once

#ifndef _OBJ_EFFECT_
#define _OBJ_EFFECT_

#include "ImageLayer/ImageLayer.h"
#include "Objects/Effect/EffectIntf.h"
#include "Objects/Effect/EffectImpl.h"

Effect createEffect(ImageLayer *imageLayer) {
  Effect newEffect = (Effect) {
    .image = &imageLayer->images[3],
    .imageLayer = imageLayer,
    .render = _Effect_render,
    .addBackgroundThread = _Effect_addBackgroundThread,
  };
  return newEffect;
}

#endif
