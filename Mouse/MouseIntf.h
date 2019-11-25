#pragma once

#ifndef _MOUSE_INTF_
#define _MOUSE_INTF_

#include <stdio.h>
#include <Windows.h>

typedef struct _Mouse {
  int x, y;
  int (*isClicked)();
  void (*updatePosition)(struct _Mouse*);
} Mouse;

#endif
