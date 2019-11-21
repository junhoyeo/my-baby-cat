#pragma once

#ifndef _OBJ_SCORE_INTF_
#define _OBJ_SCORE_INTF_

typedef struct _Score {
  int score;
  int x, y;

  void (*init)(struct _Score*);
  void (*update)(struct _Score*, int);
  void (*render)(struct _Score*);
  void (*save)(struct _Score*, char*);
} Score;

#endif
