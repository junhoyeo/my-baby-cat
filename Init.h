#pragma once

#ifndef _INIT_
#define _INIT_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <Windows.h>
#include "Utils.h"

#define SCREEN_HEIGHT 30
#define SCREEN_WIDTH 120

HANDLE CONSOLE_INPUT, CONSOLE_OUTPUT;
HWND WINDOW_HANDLE;
int DPI_HANDLE;

// int POINT_WIDTH;

inline void updateHandles() {
  CONSOLE_INPUT = GetStdHandle(STD_INPUT_HANDLE);
  CONSOLE_OUTPUT = GetStdHandle(STD_OUTPUT_HANDLE);
  WINDOW_HANDLE = GetConsoleWindow();
}

inline void updateDpiHandle() {
  HANDLE user32 = GetModuleHandle(TEXT("user32"));
  FARPROC func = GetProcAddress(user32, "GetDpiForWindow");
  if (func == NULL)
    DPI_HANDLE = 96;
  else
    DPI_HANDLE = ((UINT(__stdcall*)(HWND))func)(WINDOW_HANDLE);
}

inline void hideConsoleCursor() {
  CONSOLE_CURSOR_INFO cursorInfo;
  cursorInfo.dwSize = 100;
  cursorInfo.bVisible = FALSE;
  SetConsoleCursorInfo(CONSOLE_OUTPUT, &cursorInfo);
}

inline void disableConsoleResize() {
  LONG windowLong = GetWindowLong(WINDOW_HANDLE, GWL_STYLE);
  SetWindowLong(WINDOW_HANDLE, GWL_STYLE, windowLong & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
}

inline void disableConsoleSelection() {
  DWORD prevConsoleMode;
  GetConsoleMode(CONSOLE_INPUT, &prevConsoleMode);
  SetConsoleMode(
    CONSOLE_INPUT,
    ENABLE_EXTENDED_FLAGS | (prevConsoleMode & ~ENABLE_QUICK_EDIT_MODE)
  );
}

inline void resizeConsole(int height, int width) {
  char command[100];
  sprintf_s(command, 100, "mode con cols=%d lines=%d", width, height);
  system(command);
}

inline void initWindow() {
  updateHandles();
  updateDpiHandle();
  hideConsoleCursor();
  disableConsoleResize();
  disableConsoleSelection();
  resizeConsole(SCREEN_HEIGHT, SCREEN_WIDTH);
}

#endif
