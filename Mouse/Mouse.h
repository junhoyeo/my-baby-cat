#pragma once

#ifndef _MOUSE_
#define _MOUSE_

#include "Mouse/MouseIntf.h"
#include "Mouse/MouseImpl.h"

const Mouse DEFAULT_MOUSE = {
  { 0, 0, },
  _Mouse_isClicked,
  _Mouse_updatePosition,
};

#endif
