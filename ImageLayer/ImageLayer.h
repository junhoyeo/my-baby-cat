#pragma once
#include "ImageLayerInterface.h"
#include "ImageLayerImpl.h"

// 승현이가 만든 ImageLayer 라이브러리입니다. 변경한 점 위주로 주석을 달겠습니다.
const ImageLayer DEFAULT_IMAGE_LAYER = {
  NULL, 0, RGB(0, 9, 255), // 투명색으로 #0009FF를 지정합니다.
  NULL, NULL,
  _initialize,
  _renderAll,
  // _renderAndFadeIn,
  // _renderAndFadeOut
};
