#pragma once

#ifndef _OBJ_LIFE_
#define _OBJ_LIFE_

#include "Objects/Life/LifeIntf.h"
#include "Objects/Life/LifeImpl.h"

Life LIFE;

// 생명 오브젝트를 생성합니다.
Life createLife() {
  return (Life) {
    .hp = 100.0, // 사용자 생명
    .image = NULL,
    .imageLayer = NULL,

    .update = _Life_update,
    .render = _Life_render,
  };
}

#endif
