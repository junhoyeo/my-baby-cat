#pragma once

#ifndef _OBJ_FISH_
#define _OBJ_FISH_

#include "Resources.h"
#include "Objects/Fish/FishIntf.h"
#include "Objects/Fish/FishImpl.h"

const Fish DEFAULT_FISH = {
  0, // level
  0, 0, // x, y
  0, 0, // width, height
  0, // isMoving
  { 0, 0 }, { 0, 0 }, // start, end
  NULL, // image
  NULL, // imageLayer

  _Fish_init,
  _Fish_update,
  _Fish_move,
  _Fish_waitForEnd,
  _Fish_addBackgroundThread,
};

#endif
