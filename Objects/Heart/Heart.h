#pragma once

#ifndef _OBJ_HEART_
#define _OBJ_HEART_

#include "Objects/Heart/HeartIntf.h"
#include "Objects/Heart/HeartImpl.h"

Heart HEART;

Heart createHeart() {
  return (Heart) {
    .hp = 100.0,
    .image = NULL,
    .imageLayer = NULL,

    .update = _Heart_update,
    .render = _Heart_render,
  };
}

#endif
