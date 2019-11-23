#pragma once

#ifndef _STAGE_INTF_
#define _STAGE_INTF_

#include "Keyframe/Keyframe.h"
#include "ImageLayer/ImageLayer.h"

typedef struct _Stage {
  Keyframe *keyframes;
  int length;
  Image *image; // stage name image
  ImageLayer *imageLayer;

  void (*init)(struct _Stage*);
  void (*render)(struct _Stage*); // 이름 렌더링
  void (*update)(struct _Stage*); // 키프레임 업데이트
  void (*addBackgroundThread)(struct _Stage*, void (*method)(struct _Stage*));
} Stage;

#endif
