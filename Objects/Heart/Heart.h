#pragma once

#ifndef _OBJ_HEART_
#define _OBJ_HEART_

#include "Objects/Heart/HeartIntf.h"
#include "Objects/Heart/HeartImpl.h"

const Heart DEFAULT_HEART = {
  100,
  NULL,
  NULL,

  _Heart_update,
  _Heart_render,
}

#endif
