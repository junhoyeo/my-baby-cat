#pragma once

#ifndef _OBJ_OBSTACLE_
#define _OBJ_OBSTACLE_

#include "Objects/Obstacle/ObstacleIntf.h"
#include "Objects/Obstacle/ObstacleImpl.h"

const Obstacle DEFAULT_OBSTACLE = {
  0,
  POSITION_BOTTOM,
  0, 0,
  NULL,
  NULL,

  _Obstacle_init,
  _Obstacle_update,
  _Obstacle_move,
};

#endif
