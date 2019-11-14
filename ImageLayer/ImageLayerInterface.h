#pragma once
#include <Windows.h>

typedef struct {
	char* fileName;
	int x, y;
	double scale;
}Image;

typedef struct _ImageLayer {
	Image* images;
	int imageCount;
	UINT transparentColor;

	HWND _windowHandle;
	HDC _consoleDC;

	void (*initialize)(struct _ImageLayer*);
	void (*renderAll)(struct _ImageLayer*);
	void (*fadeIn)(struct _ImageLayer*, void(*applyToBackDC)(HDC));
	void (*fadeOut)(struct _ImageLayer*, void(*applyToBackDC)(HDC));
}ImageLayer;
