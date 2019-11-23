#pragma once

#ifndef _KEYFRAME_INTF_
#define _KEYFRAME_INTF_

#define KEYFRAME_TYPE_FISH 0
#define KEYFRAME_TYPE_OBSTACLE_BOTTOM 1
#define KEYFRAME_TYPE_OBSTACLE_TOP 2
#define KEYFRAME_TYPE_ITEM_LIFE 3
#define KEYFRAME_TYPE_ITEM_FASTER 4
#define KEYFRAME_TYPE_ITEM_SLOWER 5
#define KEYFRAME_TYPE_ITEM_GRACE 6

typedef struct _Keyframe {
  int type;
  int size;
} Keyframe;

#endif
