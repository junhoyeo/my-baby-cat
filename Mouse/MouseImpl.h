#pragma once

#ifndef _MOUSE_IMPL_
#define _MOUSE_IMPL_

#include <Windows.h>
#include "Mouse/MouseIntf.h"

inline int keyPressed(int key){
	return ((GetAsyncKeyState(key) & 0x8000) != 0);
}

inline int _Mouse_isClicked() {
	if (keyPressed(VK_LBUTTON)) return 1;
	if (keyPressed(VK_RBUTTON)) return 2;
	return 0;
}

inline void _Mouse_updatePosition(Mouse* self) {
  POINT cursor;
  GetCursorPos(&cursor);
  ScreenToClient(WINDOW_HANDLE, &cursor);
  self->pos.X = cursor.x;
  self->pos.Y = cursor.y;
}

#endif
