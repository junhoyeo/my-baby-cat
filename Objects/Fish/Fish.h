#pragma once

#ifndef _OBJ_FISH_
#define _OBJ_FISH_

#include "Resources.h"
#include "Objects/Fish/FishIntf.h"
// #include "Objects/Fish/FishImpl.h"

const Fish DEFAULT_FISH = {
  0, 0,
  0, 0,
  { 0, 0, }, { 0, 0, },
  NULL,
  NULL,

  _Cat_init,
  // _Cat_update,
  // _Cat_isHovered,
  // _Cat_waitForMouse,
  // _Cat_move,
  // _Cat_run,
  // _Cat_addBackgroundThread,
};

#endif
