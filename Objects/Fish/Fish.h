#pragma once

#ifndef _OBJ_FISH_
#define _OBJ_FISH_

#include "Resources.h"
#include "Objects/Fish/FishIntf.h"
#include "Objects/Fish/FishImpl.h"

const Fish DEFAULT_FISH = {
  0,
  0, 0,
  0, 0,
  { 0, 0, }, { 0, 0, },
  NULL,
  NULL,

  _Fish_init,
  _Fish_update,
  _Fish_move,
};

#endif
