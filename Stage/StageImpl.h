#pragma once

#ifndef _STAGE_IMPL_
#define _STAGE_IMPL_

#include <process.h>
#include "Stage/StageIntf.h"

void _Stage_init(Stage* self) {
  return;
}

void _Stage_render(Stage* self) {
  return;
}

void _Stage_addBackgroundThread(Stage* self, int (*method)(Stage*)) {
  _beginthread(*method, 0, (Stage*) self);
}

#endif
