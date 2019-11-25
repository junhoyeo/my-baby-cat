#pragma once

#ifndef _SPEED_
#define _SPEED_

typedef struct _Speed {
  int delay;

  void (*init)(struct _Speed*);
  void (*increase)(struct _Speed*);
  void (*decrease)(struct _Speed*);
  void (*addBackgroundThread)(struct _Speed*, void (*method)(struct _Speed*));
} Speed;

// 게임이 시작되자마자 일정 속도가 될 때까지 속도를 점차 높입니다.
void _Speed_init(Speed* self) {
  for (int speed = self->delay; speed > 50; speed-=20) {
    Sleep(800);
    self->delay = speed;
  }
}

// 서서히 딜레이 값을 80 줄입니다. 1초 유지 후 바로 80를 올립니다.
void _Speed_increase(Speed*self) {
  for (int i = 0; i < 5; i++) {
    Sleep(10);
    self->delay += 16;
  }
  Sleep(1000);
  self->delay += 80;
}

// 서서히 딜레이 값을 25 늘립니다. 3초 유지 후 바로 25를 줄입니다.
void _Speed_decrease(Speed*self) {
  for (int i = 0; i < 5; i++) {
    Sleep(50);
    self->delay += 5;
  }
  Sleep(3000);
  self->delay -= 25;
}

// 백그라운드 스레드를 시작합니다.
void _Speed_addBackgroundThread(Speed* self, int (*method)(Speed*)) {
  _beginthread(*method, 0, (Speed*) self);
}

// 처음 시작 딜레이는 150, 시작하자마자 50으로 점점 줄어들어 고정
// 아이템 먹으면 일정 시간 동안 증감 효과
// 장애물 부딪히면 일정 시간 동안 낮아짐

Speed SPEED;

// 새로운 속도 오브젝트를 생성합니다.
Speed createSpeed() {
  return (Speed) {
    .delay = 150,
    .init = _Speed_init,
    .increase = _Speed_increase,
    .decrease = _Speed_decrease,
    .addBackgroundThread = _Speed_addBackgroundThread,
  };
}

#endif
