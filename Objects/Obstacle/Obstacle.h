#pragma once

#ifndef _OBJ_OBSTACLE_
#define _OBJ_OBSTACLE_

#include <stdbool.h>
#include "Resources.h"
#include "Objects/Obstacle/ObstacleIntf.h"
#include "Objects/Obstacle/ObstacleImpl.h"

const Obstacle DEFAULT_OBSTACLE = {
  POSITION_BOTTOM,
  0, 0,
  NULL,
  NULL,

  _Obstacle_init,
  _Obstacle_update,
  _Obstacle_move,
};

// 위치에 따른 장애물 종류(위: 슬라이드로 피함/아래: 점프로 피함)에 따라 랜덤 장애물을 생성해 반환합니다.
Obstacle createObstacleByPos(ImageLayer* imageLayer, int pos) {
  Obstacle newObstacle = DEFAULT_OBSTACLE;
  imageLayer->imageCount++;
  Image *images = imageLayer->images;
  int imageIndex = imageLayer->imageCount - 1;

  // 종류에 따른 랜덤 장애물 이미지를 가져옵니다.
  char *fileName = (!pos) ?
    RESOURCE_OBST_BOTTOM[randrange(RESOURCE_OBST_BOTTOM_LEN)] :
    RESOURCE_OBST_TOP[randrange(RESOURCE_OBST_TOP_LEN)];

  images[imageIndex] = (Image) {
    .fileName = fileName,
    .x = 0,
    .y = 0,
    .scale = 1,
    .isShown = false,
  };
  // imageLayer->imageCount++;

  newObstacle.image = &images[imageIndex];
  newObstacle.imageLayer = imageLayer;
  newObstacle.init(&newObstacle, pos);
  return newObstacle;
}

#endif
