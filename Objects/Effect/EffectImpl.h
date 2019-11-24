#pragma once

#ifndef _OBJ_EFFECT_IMPL_
#define _OBJ_EFFECT_IMPL_

#include <stdbool.h>
#include <process.h>
#include "Resources.h"
#include "Objects/Effect/EffectIntf.h"

void _Effect_render(Effect *self) {
  self->image->isShown = true;
  for (int i = 0; i < 10; i++) {
    self->image->fileName = RESOURCE_EFFECT[i];
    Sleep(100);
  }
  self->image->isShown = false;
}

void _Effect_addBackgroundThread(Effect* self, void (*method)(Effect*)) {
  _beginthread(*method, 0, (Effect*) self);
}

#endif
