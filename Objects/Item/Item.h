#pragma once

#ifndef _OBJ_ITEM_
#define _OBJ_ITEM_

#include "Objects/Item/ItemIntf.h"
#include "Objects/Item/ItemImpl.h"

const Item DEFAULT_ITEM = {
  .x = 0,
  .y = 0,
  .width = 0,
  .height = 0,
  .image = NULL,
  .imageLayer = NULL,

  .init = _Item_init,
  .update = _Item_update,
  .move = _Item_move,
};

#endif
