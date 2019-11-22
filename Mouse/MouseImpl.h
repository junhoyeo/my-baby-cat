#pragma once

#ifndef _MOUSE_IMPL_
#define _MOUSE_IMPL_

#include <Windows.h>
#include "Mouse/MouseIntf.h"

// 열심히 만들었으나 결국 사용하지 못하게 된 마우스 라이브러리입니다.

// GetAsyncKeyState의 wrapper로 특정 키의 상태를 반환합니다.
inline int keyPressed(int key){
	return ((GetAsyncKeyState(key) & 0x8000) != 0);
}

// 마우스 입력을 감지합니다.
inline int _Mouse_isClicked() {
	if (keyPressed(VK_LBUTTON)) return 1;
	if (keyPressed(VK_RBUTTON)) return 2;
	return 0;
}

// 마우스 포지션을 업데이트합니다. 다른 쓰레드에서 돌리거나 해야 합니다.
inline void _Mouse_updatePosition(Mouse* self) {
  POINT cursor;
  GetCursorPos(&cursor);
  ScreenToClient(WINDOW_HANDLE, &cursor);
  self->pos.X = cursor.x;
  self->pos.Y = cursor.y;
}

#endif
