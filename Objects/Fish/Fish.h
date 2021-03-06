﻿#pragma once

#ifndef _OBJ_FISH_
#define _OBJ_FISH_

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
  _Fish_updateRandomLevel,
  // _Fish_waitForEnd,
  // _Fish_addBackgroundThread,
};

// startX를 시작 위치로 가지는 새로운 Fish 객체를 반환합니다.
Fish createFish(int startX) {
  Fish fish = DEFAULT_FISH;
  fish.x = startX;
  fish.y = 600;
  return fish;
}

#endif
