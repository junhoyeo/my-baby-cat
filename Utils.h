#pragma once

#ifndef _UTILS_
#define _UTILS_

#include <time.h>
#include <Windows.h>

#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH 480

void gotoxy(int x, int y) {
  COORD pos = { x, y };
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int randrange(int max) {
  // 0 ~ (max - 1) 사이의 값을 반환합니다.
  return (int)(rand() % max);
}

COLORREF hexToColor(int hex) {
  int red = hex / 0x10000;
  int green = (hex / 0x100) % 0x100;
  int blue = hex % 0x100;
  return RGB(red, green, blue);
}

#endif
