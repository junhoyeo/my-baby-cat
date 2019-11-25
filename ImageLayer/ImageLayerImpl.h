#pragma once
#pragma comment (lib, "Msimg32.lib")

#include <Windows.h>
#include "ImageLayer.h"

int CONSOLE_WIDTH = 120;
int CONSOLE_HEIGHT = 35;

#define DEFAULT_RESOLUTION_SCALE 16
double RESOLUTION_MULTIPLIER = 1;
int windowWidth = 0;
int windowHeight = 0;

typedef struct {
  int width, height;
} Size;

// 현재 DPI를 가져옵니다.
inline int getDPI(HWND hWnd) {
  const HANDLE user32 = GetModuleHandle(TEXT("user32"));
  const FARPROC func = GetProcAddress(user32, "GetDpiForWindow");
  if (func == NULL)
    return 96;
  return ((UINT(__stdcall*)(HWND))func)(hWnd);
}

// 비트맵을 인수로 받아 그 크기를 반환하는 함수입니다.
inline Size getBitmapSize(HBITMAP bitmap) {
  BITMAP tmpBitmap;
  GetObject(bitmap, sizeof(BITMAP), &tmpBitmap);
  const Size bitmapSize = { tmpBitmap.bmWidth, tmpBitmap.bmHeight };
  return bitmapSize;
}

// 새로운 검정색 DC를 반환합니다.
inline HDC createNewBackDC(HDC compatibleDC) {
  const HDC backDC = CreateCompatibleDC(compatibleDC);
  const HBITMAP backBitmap = CreateCompatibleBitmap(compatibleDC, windowWidth, windowHeight);
  SelectObject(backDC, backBitmap);
  DeleteObject(backBitmap);
  return backDC;
}

// DC에 인수로 들어온 이미지를 그립니다.
inline void putBitmapToBackDC(HDC backDC, Image image, UINT transparentColor) {
  const HDC bitmapDC = CreateCompatibleDC(backDC);
  const HBITMAP bitmap = (HBITMAP)LoadImage(NULL, (LPCSTR)image.fileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
  SelectObject(bitmapDC, bitmap);

  double scale = image.scale;
  if (scale == 0) scale = DEFAULT_RESOLUTION_SCALE * RESOLUTION_MULTIPLIER;

  const int x = (int)(image.x * RESOLUTION_MULTIPLIER);
  const int y = (int)(image.y * RESOLUTION_MULTIPLIER);
  const Size bitmapSize = getBitmapSize(bitmap);
  const int width = (int)(bitmapSize.width * scale);
  const int height = (int)(bitmapSize.height * scale);
  TransparentBlt(backDC, x, y, width, height,
    bitmapDC, 0, 0, bitmapSize.width, bitmapSize.height, transparentColor);

  DeleteObject(bitmap);
  DeleteDC(bitmapDC);
}

// dstDC에 srcDC를 복사합니다.
inline void applyToDC(HDC dstDC, HDC srcDC) {
  BitBlt(dstDC, 0, 0, windowWidth, windowHeight,
    srcDC, 0, 0, SRCCOPY);
}

// ImageLayer를 초기화합니다.
inline void _initialize(ImageLayer* self) {
  self->_windowHandle = GetConsoleWindow();
  self->_consoleDC = GetDC(self->_windowHandle);

  const int dpi = getDPI(self->_windowHandle);
  RESOLUTION_MULTIPLIER = dpi / 192.0;
  windowWidth = (int)(CONSOLE_WIDTH * DEFAULT_RESOLUTION_SCALE * RESOLUTION_MULTIPLIER);
  windowHeight = (int)(CONSOLE_HEIGHT * 2 * DEFAULT_RESOLUTION_SCALE * RESOLUTION_MULTIPLIER);
}

// 모든 이미지가 렌더링된 DC를 반환합니다.
inline HDC getRenderedBackDC(ImageLayer* self) {
  const HDC backDC = createNewBackDC(self->_consoleDC);

  for (int i = 0; i < self->imageCount; i++) {

    // isShown 값이 거짓인 이미지는 렌더링되지 않도록 수정했습니다.
    if (!self->images[i].isShown)
      continue;

    putBitmapToBackDC(backDC, self->images[i], self->transparentColor);
  }
  return backDC;
}

// 화면에 렌더링된 DC를 표시합니다.
inline void _renderAll(ImageLayer* self) {
  const HDC backDC = getRenderedBackDC(self);
  applyToDC(self->_consoleDC, backDC);
  DeleteDC(backDC);
}
