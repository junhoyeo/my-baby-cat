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

inline int getDPI(HWND hWnd) {
  const HANDLE user32 = GetModuleHandle(TEXT("user32"));
  const FARPROC func = GetProcAddress(user32, "GetDpiForWindow");
  if (func == NULL)
    return 96;
  return ((UINT(__stdcall*)(HWND))func)(hWnd);
}

inline Size getBitmapSize(HBITMAP bitmap) {
  BITMAP tmpBitmap;
  GetObject(bitmap, sizeof(BITMAP), &tmpBitmap);
  const Size bitmapSize = { tmpBitmap.bmWidth, tmpBitmap.bmHeight };
  return bitmapSize;
}

inline HDC createNewBackDC(HDC compatibleDC) {
  const HDC backDC = CreateCompatibleDC(compatibleDC);
  const HBITMAP backBitmap = CreateCompatibleBitmap(compatibleDC, windowWidth, windowHeight);
  SelectObject(backDC, backBitmap);
  DeleteObject(backBitmap);
  return backDC;
}

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

inline void applyToDC(HDC dstDC, HDC srcDC) {
  BitBlt(dstDC, 0, 0, windowWidth, windowHeight,
    srcDC, 0, 0, SRCCOPY);
}

inline void _initialize(ImageLayer* self) {
  self->_windowHandle = GetConsoleWindow();
  self->_consoleDC = GetDC(self->_windowHandle);

  const int dpi = getDPI(self->_windowHandle);
  RESOLUTION_MULTIPLIER = dpi / 192.0;
  windowWidth = (int)(CONSOLE_WIDTH * DEFAULT_RESOLUTION_SCALE * RESOLUTION_MULTIPLIER);
  windowHeight = (int)(CONSOLE_HEIGHT * 2 * DEFAULT_RESOLUTION_SCALE * RESOLUTION_MULTIPLIER);
}

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

inline void _renderAll(ImageLayer* self) {
  const HDC backDC = getRenderedBackDC(self);
  applyToDC(self->_consoleDC, backDC);
  DeleteDC(backDC);
}

inline BLENDFUNCTION getBlendFunction() {
  BLENDFUNCTION bf;
  bf.AlphaFormat = AC_SRC_ALPHA;
  bf.BlendFlags = 0;
  bf.BlendOp = AC_SRC_OVER;
  bf.SourceConstantAlpha = 0;
  return bf;
}

// 개발 당시 사용하지 않는 함수를 임시로 주석처리했으나 영영 사용하지 못할 것 같습니다...

// inline void _renderAndFadeIn(ImageLayer* self, void(*applyToBackDC)(HDC)) {
//   const HDC consoleDC = self->_consoleDC;
//   const HDC backDC = getRenderedBackDC(self);
//   if (applyToBackDC != NULL) applyToBackDC(backDC);

//   const HBRUSH blackBrush = CreateSolidBrush(RGB(0, 0, 0));
//   SelectObject(consoleDC, blackBrush);

//   BLENDFUNCTION bf = getBlendFunction();
//   bf.SourceConstantAlpha = 12;

//   Rectangle(consoleDC, 0, 0, windowWidth, windowHeight);
//   for (int i = 0; i < 20; i++) {
//     AlphaBlend(consoleDC, 0, 0, windowWidth, windowHeight,
//       backDC, 0, 0, windowWidth, windowHeight, bf);
//   }
//   applyToDC(consoleDC, backDC);
//   DeleteObject(blackBrush);
//   DeleteDC(backDC);
// }

// inline void _renderAndFadeOut(ImageLayer* self, void(*applyToBackDC)(HDC)) {
//   const HDC consoleDC = self->_consoleDC;
//   const HDC backDC = getRenderedBackDC(self);
//   if (applyToBackDC != NULL) applyToBackDC(backDC);
//   applyToDC(consoleDC, backDC);

//   const HDC blackDC = createNewBackDC(consoleDC);
//   BLENDFUNCTION bf = getBlendFunction();

//   for (int i = 255; i >= 0; i -= 20) {
//     bf.SourceConstantAlpha = i;
//     applyToDC(consoleDC, blackDC);
//     AlphaBlend(consoleDC, 0, 0, windowWidth, windowHeight,
//       backDC, 0, 0, windowWidth, windowHeight, bf);
//     Sleep(100);
//   }
//   applyToDC(consoleDC, blackDC);

//   DeleteDC(backDC);
//   DeleteDC(blackDC);
// }
