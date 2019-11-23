#pragma once

#ifndef _ANIMATE_ITEM_
#define _ANIMATE_ITEM_

#include <Windows.h>
#include "Animate/Animate.h"
#include "Objects/Cat/Cat.h"
#include "Objects/Item/Item.h"
#include "ImageLayer/ImageLayer.h"

Item *(*ItemSegmentPointer)[] = NULL;
int _animateItemSegments_shown = 0;

void animateItemSegments(AnimateProps* animateProps) {
  Cat *cat = animateProps->cat;
  int itemLength = animateProps->objectLength;
  while (1) {
    for (int idx = 0; idx < itemLength; idx++) {
      Sleep(SPEED.delay / 1.5);
      (*ItemSegmentPointer)[idx]->move((*ItemSegmentPointer)[idx], 20);
      if ((*ItemSegmentPointer)[idx]->x <= 1500) {
        _animateItemSegments_shown++;
      }
    }
  }
}

#endif
