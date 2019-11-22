#pragma once

#ifndef _OBJ_HEART_
#define _OBJ_HEART_

#include "Objects/Heart/HeartIntf.h"
#include "Objects/Heart/HeartImpl.h"

Heart HEART;

// 체력 오브젝트를 생성합니다.
Heart createHeart() {
  return (Heart) {
    .hp = 100.0, // 사용자 체력
    .image = NULL,
    .imageLayer = NULL,

    .update = _Heart_update,
    .render = _Heart_render,
  };
}

#endif
