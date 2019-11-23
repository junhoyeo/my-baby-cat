#pragma once

#ifndef _SPEED_
#define _SPEED_

typedef struct _Speed {
  int delay;

  void (*init)(struct _Speed*);
  void (*addBackgroundThread)(struct _Speed*, void (*method)(struct _Speed*));
} Speed;

void _Speed_init(Speed* self) {
  for (int speed = self->delay; speed > 50; speed-=20) {
    Sleep(800);
    self->delay = speed;
    gotoxy(0,0);
    printf("[%d]\n", self->delay);
  }
}

void _Speed_increase(Speed*self) {
  
}

void _Speed_decrease(Speed*self) {
  
}

void _Speed_addBackgroundThread(Speed* self, int (*method)(Speed*)) {
  _beginthread(*method, 0, (Speed*) self);
}

// 처음 시작 딜레이는 150, 시작하자마자 50으로 점점 줄어들어 고정
// 아이템 먹으면 일정 시간 동안 증감 효과
// 장애물 부딪히면 일정 시간 동안 낮아짐

Speed SPEED;

Speed createSpeed() {
  return (Speed) {
    .delay = 150,
    .init = _Speed_init,
    .addBackgroundThread = _Speed_addBackgroundThread,
  };
}

#endif
