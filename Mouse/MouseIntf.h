#pragma once

#ifndef _MOUSE_INTF_
#define _MOUSE_INTF_

#include <stdio.h>
#include <Windows.h>

typedef struct _Mouse {
  COORD pos;
  int (*isClicked)();
  void (*updatePosition)(struct _Mouse*);
} Mouse;

#endif
