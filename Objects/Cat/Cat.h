#pragma once

#ifndef _OBJ_CAT_
#define _OBJ_CAT_

#include "Resources.h"
#include "ImageLayer/ImageLayer.h"
#include "Objects/Cat/CatIntf.h"
#include "Objects/Cat/CatImpl.h"

const Cat DEFAULT_CAT = {
  0, 0,
  0, 0,
  0,
  180.0, // delay for running speed
  { 0, 0, }, { 0, 0, },
  NULL,
  NULL,

  _Cat_init,
  _Cat_update,
  // _Cat_isHovered,
  // _Cat_waitForMouse,
  _Cat_move,
  _Cat_run,
  _Cat_jump,
  _Cat_slide,
  _Cat_listenKeys,
  _Cat_addBackgroundThread,
};

#endif
