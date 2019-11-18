#pragma once

#ifndef _OBJ_FISH_INTF_
#define _OBJ_FISH_INTF_

#include <Windows.h>

typedef struct _Fish {
  int x, y;
  int width, height;
  COORD start, end;
} Fish;

#endif
