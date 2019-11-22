#pragma once

#ifndef _UTILS_
#define _UTILS_

#include <time.h>
#include <Windows.h>

#define WINDOW_HEIGHT 800
#define WINDOW_WIDTH 480

// x, y 위치로 커셔를 이동시키는 gotoxy 함수의 구현체입니다.
// 거의 디버깅 목적으로만 사용했습니다.
void gotoxy(int x, int y) {
  COORD pos = { x, y };
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// 0 ~ (max - 1) 사이의 값을 반환하는 함수입니다.
// 시드 초기화는 Init.h의 initWindow() 에서 이루어집니다.
int randrange(int max) {
  return (int)(rand() % max);
}

// 0xFFFFFF와 같은 16진수 색을 COLORREF 구조로 변환하는 함수입니다.
// hexToColor(0xFFFFFF) 등으로 사용하면 매우 편리합니다.
COLORREF hexToColor(int hex) {
  int red = hex / 0x10000;
  int green = (hex / 0x100) % 0x100;
  int blue = hex % 0x100;
  return RGB(red, green, blue);
}

#endif
