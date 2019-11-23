#pragma once

#ifndef _OBJ_CAT_
#define _OBJ_CAT_

#include "Resources.h"
#include "ImageLayer/ImageLayer.h"
#include "Objects/Cat/CatIntf.h"
#include "Objects/Cat/CatImpl.h"

const Cat DEFAULT_CAT = {
  .x = 0,
  .y = 0,
  .width = 0,
  .height = 0,
  .isRunning = 0,
  .isSliding = false,
  .start = { 0, 0, },
  .end = { 0, 0, },
  .image = NULL,
  .imageLayer = NULL,

  .init = _Cat_init,
  .update = _Cat_update,
  .move = _Cat_move,
  .run = _Cat_run,
  .jump = _Cat_jump,
  .slide = _Cat_slide,
  .listenKeys = _Cat_listenKeys,
  .addBackgroundThread = _Cat_addBackgroundThread,
};

#endif
