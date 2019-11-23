#pragma once

#ifndef _KEYFRAME_INTF_
#define _KEYFRAME_INTF_

#define KEYFRAME_TYPE_FISH 0
#define KEYFRAME_TYPE_OBSTACLE_BOTTOM 1
#define KEYFRAME_TYPE_OBSTACLE_TOP 2
#define KEYFRAME_TYPE_ITEM 3

typedef struct _Keyframe {
  int type;
  int effect;
  int size;
} Keyframe;

#endif
