#pragma once

#ifndef _INIT_
#define _INIT_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <conio.h>
#include <Windows.h>
#include "Utils.h"
#include "Objects/Life/Life.h"
#include "Objects/Score/Score.h"

#define SCREEN_HEIGHT 30
#define SCREEN_WIDTH 120

HANDLE CONSOLE_INPUT, CONSOLE_OUTPUT;
HWND WINDOW_HANDLE;
int DPI_HANDLE;

// (전역변수로 등록되는) 콘솔, 윈도우 핸들을 가져옵니다.
inline void updateHandles() {
  CONSOLE_INPUT = GetStdHandle(STD_INPUT_HANDLE);
  CONSOLE_OUTPUT = GetStdHandle(STD_OUTPUT_HANDLE);
  WINDOW_HANDLE = GetConsoleWindow();
}

// DPI 핸들을 가져옵니다.
inline void updateDpiHandle() {
  HANDLE user32 = GetModuleHandle(TEXT("user32"));
  FARPROC func = GetProcAddress(user32, "GetDpiForWindow");
  if (func == NULL)
    DPI_HANDLE = 96;
  else
    DPI_HANDLE = ((UINT(__stdcall*)(HWND))func)(WINDOW_HANDLE);
}

// 콘솔 커셔를 숨깁니다.
inline void hideConsoleCursor() {
  CONSOLE_CURSOR_INFO cursorInfo;
  cursorInfo.dwSize = 100;
  cursorInfo.bVisible = FALSE;
  SetConsoleCursorInfo(CONSOLE_OUTPUT, &cursorInfo);
}

// 사용자가 콘솔 창의 크기를 마음대로 변경하지 못하게 합니다.
inline void disableConsoleResize() {
  LONG windowLong = GetWindowLong(WINDOW_HANDLE, GWL_STYLE);
  SetWindowLong(WINDOW_HANDLE, GWL_STYLE, windowLong & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
}

// Quick Edit 모드를 비활성화해서 사용자가 콘솔 창을 드래그하지 못하게 합니다.
// 드래그 시 찍은 픽셀이나 이미지가 지워질 수 있기 때문입니다.
inline void disableConsoleSelection() {
  DWORD prevConsoleMode;
  GetConsoleMode(CONSOLE_INPUT, &prevConsoleMode);
  SetConsoleMode(
    CONSOLE_INPUT,
    ENABLE_EXTENDED_FLAGS | (prevConsoleMode & ~ENABLE_QUICK_EDIT_MODE)
  );
}

// height, width 만큼의 글자 수가 들어가도록 콘솔 창의 크기를 변경합니다.
inline void resizeConsole(int height, int width) {
  char command[100];
  sprintf_s(command, 100, "mode con cols=%d lines=%d", width, height);
  system(command);
}

// 위에 있는 함수들을 순차적으로 호출해서 윈도우를 초기화하는 함수입니다.
inline void initWindow() {
  updateHandles();
  updateDpiHandle();
  hideConsoleCursor();
  disableConsoleResize();
  disableConsoleSelection();
  resizeConsole(SCREEN_HEIGHT, SCREEN_WIDTH);

  // 랜덤 시드를 초기화합니다.
  srand((unsigned)time(NULL));

  // 생명 바 오브젝트를 생성합니다.
  LIFE = createLife();

  // 점수 오브젝트를 생성합니다.
  SCORE = createScore();
}

#endif
