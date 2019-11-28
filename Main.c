/*
My Baby Cat
---------------
MIT License
Copyright (c) 2019 JUNO, Woo-sang yun

My Baby Cat은 앞으로 달려가는 고양이를 조종해
최대한 오래 살아남아 많은 점수를 얻는 게임이다.
쿠키런에서 모티브를 얻었다.
고양이의 속도는 점점 빨라지고, 이와 동시에 체력 또한 점점 줄어든다.
스페이스 바를 눌러 점프할 수 있고, 방향키(아래)를 눌러 슬라이딩을 할 수 있으며,
이를 통해 장애물을 피할 수 있다.
만약 장애물에 충돌할 시 체력이 줄어들게 된다.
고양이가 생선에 닿으면 점수가 올라가며, 아이템에 닿을 시 체력 회복,
이동 속도 변경 등의 효과가 적용된다.
최대한 많은 생선을 먹어 최고점수를 갱신해 나가는 것이 게임의 목표이고,
쉽고 간단한 조작법, 그래픽으로 모두가 좋아할 만한 게임을 만들기 위해 노력했다.
자세한 게임 문서는 공식 문서 사이트에서 확인할 수 있다.

공식 문서 사이트: http://junhoyeo.github.io/my-baby-cat
프로젝트 깃허브: https://github.com/junhoyeo/my-baby-cat
*/

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4024)
#pragma warning(disable: 4047)
#pragma warning(disable: 4224)
#pragma warning(disable: 4819)
#pragma comment(lib, "winmm.lib")
#endif

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <process.h>
#include <Windows.h>

#include "Init.h"
#include "Utils.h"
#include "Speed.h"
#include "Lobby.h"

#include "Mouse/Mouse.h"
#include "Keyframe/Keyframe.h"
#include "Stage/Stage.h"
#include "ImageLayer/ImageLayer.h"

#include "Objects/Cat/Cat.h"
#include "Objects/Fish/Fish.h"
#include "Objects/Obstacle/Obstacle.h"
#include "Objects/Item/Item.h"

#include "Animate/Animate.h"
#include "Animate/AnimateFish.h"
#include "Animate/AnimateItem.h"
#include "Animate/AnimateObstacle.h"

#define IMAGE_BACKGROUND_IDX 0

int main() {
  // 첫 번째 실행인지를 확인할 때 사용하는 플래그입니다.
  bool firstRun = true;

  // 리소스를 업데이트합니다,
  updateResources();

  // 클릭을 감지하기 위한 마우스 객체를 생성합니다.
  Mouse mouse = DEFAULT_MOUSE;

  // ImageLayer를 초기화합니다.
  ImageLayer imageLayer = DEFAULT_IMAGE_LAYER;
  imageLayer.initialize(&imageLayer);

  // 배경음악을 재생하고, 윈도우를 초기화합니다.
  PlaySound(RESOURCE_SOUND_BGM_1, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
  initWindow();

  while (1) {
    // 사용할 이미지 배열에 메모리를 할당합니다.
    Image *images = malloc(100 * sizeof(Image));

    // 첫 번째 실행이 아닐 경우에만 초기화합니다.
    if (!firstRun) {
      // 인트로를 보여주기 좋게 윈도우 사이즈를 재조정합니다.
      resizeConsole(SCREEN_HEIGHT + 2, SCREEN_WIDTH);

      // 생명, 점수, 속도 오브젝트를 초기화합니다.
      LIFE = createLife();
      SCORE = createScore();
      SPEED = createSpeed();

      // 애니메이션 플래그를 초기화합니다.
      _animateFishSegments_finished = 0;
      _animateFishSegments_received = 0;
      _animateFishSegments_shown = 0;
      _animateItemSegments_finished = 0;
      _animateItemSegments_received = 0;
      _animateItemSegments_shown = 0;
      _animateObstacleSegments_finished = 0;
      _animateObstacleSegments_received = 0;
      _animateObstacleSegments_shown = 0;
    }

    // 0.1초 딜레이를 줍니다.
    Sleep(100);

    // 로비를 렌더링합니다.
    // 첫 번째 실행일 경우에는 로비를 보여주기 전에 타이틀을 보여주고, 그렇지 않은 경우에는 로비만 보여줍니다.
    renderLobby(&imageLayer, &mouse, (firstRun) ? true : false);

    // 실행 화면에 맞게 콘솔 사이즈를 재조정합니다.
    CONSOLE_WIDTH = 120;
    CONSOLE_HEIGHT = 30;
    resizeConsole(SCREEN_HEIGHT, SCREEN_WIDTH);

    // 각종 이미지를 초기화합니다.
    images[0] = (Image) { .fileName = RESOURCE_BACKGROUND[0], .x = 0, .y = 0, .scale = 3, .isShown = true };
    images[1] = (Image) { .fileName = RESOURCE_CAT[0], .x = 0, .y = 450, .scale = 3, .isShown = true };
    images[2] = (Image) { .fileName = RESOURCE_LIFE[20], .x = 0, .y = 0, .scale = 3, .isShown = true };
    images[3] = (Image) { .fileName = RESOURCE_EFFECT[0], .x = -50, .y = 100, .scale = 3, .isShown = false };
    images[4] = (Image) { .fileName = RESOURCE_TEXT_STAGE[0], .x = 680, .y = 100, .scale = 1.5, .isShown = false };
    for (int idx = 5; idx < 11; idx++) {
      images[idx] = (Image) {
        .fileName = RESOURCE_NUMBERS[0],
        .x = 1945 - idx * 65,
        .y = 30,
        .scale = 1,
        .isShown = true,
      };
    }
    imageLayer.imageCount = 11;
    imageLayer.images = images;

    // 고양이 객체를 초기화힙니다.
    Cat cat = DEFAULT_CAT;
    cat.image = &images[1];
    cat.imageLayer = &imageLayer;
    cat.init(&cat);

    // 생명 객체를 초기화합니다,
    LIFE.image = &images[2];
    LIFE.imageLayer = &imageLayer;

    // 점수 객체를 초기화합니다.
    for (int idx = 5; idx < 11; idx++) {
      SCORE.images[idx - 5] = &images[idx];
    }
    SCORE.imageLayer = &imageLayer;

    // 게임을 시작합니다.
    imageLayer.renderAll(&imageLayer);

    // 속도를 조금씩 줄입니다.
    SPEED.addBackgroundThread(&SPEED, SPEED.init);

    // 고양이를 달리게 합니다.
    cat.addBackgroundThread(&cat, cat.run);

    // 고양이의 점프 및 슬라이드를 감지하기 위해 리스너를 시작합니다.
    cat.addBackgroundThread(&cat, cat.listenKeys);
    // fish.addBackgroundThread(&fish, fish.move);

    // 스테이지 배열을 만들고 초기화합니다.
    Stage *stages[5];
    for (int idx = 0; idx < 5; idx++) {
      stages[idx] = malloc(sizeof(Stage));
      *stages[idx] = (Stage) {
        .index = idx,
        .keyframes = NULL,
        .length = 0,
        .image = &images[4],
        .imageLayer = &imageLayer,
        .init = _Stage_init,
        .render = _Stage_render,
        .update = NULL,
        .addBackgroundThread = _Stage_addBackgroundThread,
      };
    }

    // 각각의 스테이지에 업데이트 함수를 할당하고, 초기화합니다.
    stages[0]->update = _Stage_createStageOneKeyframes;
    stages[1]->update = _Stage_createStageTwoKeyframes;
    stages[2]->update = _Stage_createStageThreeKeyframes;
    stages[3]->update = _Stage_createStageFourKeyframes;
    stages[4]->update = _Stage_createStageFiveKeyframes;

    for (int i = 0; i < 5; i++)
      stages[i]->update(stages[i]);

    // 최대 물고기 떼, 장애물 떼, 아이템 떼는 5개까지만!
    // 여기에 각각의 개체 포인터를 저장할 스토리지를 만들어 초기화
    Fish *fishSegments[5];

    // 시간이 없으니 Bottom, Top 위치별로 따로 저장
    Obstacle *ObstacleBottomSegments[5];
    Obstacle *ObstacleTopSegments[5];
    Item *ItemSegments[5];

    // 각각의 객체 세그먼트를 저장할 배열에 메모리를 할당합니다.
    for (int i = 0; i < 5; i++) {
      fishSegments[i] = malloc(sizeof(Fish));
      *fishSegments[i] = createFish(1900 + i * 200);

      ObstacleBottomSegments[i] = malloc(sizeof(Obstacle));

      ObstacleTopSegments[i] = malloc(sizeof(Obstacle));

      ItemSegments[i] = malloc(sizeof(Item));
    }

    // 사고사로 죽었는지 체크하는 플래그입니다.
    double isDead = false;
    for (int key = 0; key < 5; key++) {
      Stage *currentStage = stages[key];

      // 스테이지 타이틀을 보여줍니다.
      currentStage->addBackgroundThread(currentStage, currentStage->render);

      // 스테이지 배경을 바꿉니다.
      images[IMAGE_BACKGROUND_IDX].fileName = RESOURCE_BACKGROUND[key];

      for (int frame = 0; frame < currentStage->length; frame++) {
        Keyframe currentFrame = currentStage->keyframes[frame];
        AnimateProps animateProps = (AnimateProps) {
          .cat = &cat,
          .objectLength = currentFrame.size,
          .objectClass = (currentFrame.type != KEYFRAME_TYPE_ITEM) ? currentFrame.type : currentFrame.effect,
        };

        // TODO: 나중에 다시 건드리게 되면 추상화시키기,,, 꼭,,,
        // 물고기 키프레임 렌더링
        if (currentFrame.type == KEYFRAME_TYPE_FISH) {
          // 이미 물고기 떼가 있으면, 다 사라질 때까지 대기한다.
          while (_animateFishSegments_finished < _animateFishSegments_received) {};

          for(int i = 0; i < currentFrame.size; i++) {
            // 물고기 위치 이동시키고 초기화
            fishSegments[i]->x = 1900 + i * 200;
            if (_animateFishSegments_received == 0) {
              images[imageLayer.imageCount] = (Image) { .fileName = RESOURCE_FISH[0], .x = 1900, .y = 600, .scale = 3, .isShown = true };
              fishSegments[i]->image = &images[imageLayer.imageCount];
              fishSegments[i]->imageLayer = &imageLayer;
              imageLayer.imageCount++;
            }
            fishSegments[i]->image->isShown = true;
            fishSegments[i]->init(fishSegments[i]);
            fishSegments[i]->updateRandomLevel(fishSegments[i]);
          }

          fishSegmentPointer = &fishSegments;

          // 각종 플래그 초기화
          _animateFishSegments_finished = 0;
          _animateFishSegments_shown = 0;
          _animateFishSegments_received = currentFrame.size;

          // 백그라운드 스레드를 만들어서 배경에서 움직이게 함
          _beginthread(animateFishSegments, 0, (AnimateProps*) &animateProps);

          // 화면에 다 보여질 때까지 기다림
          while (_animateFishSegments_shown < currentFrame.size) {};
        }

        // 아래쪽에 있는 장애물 키프레임 렌더링
        else if (currentFrame.type == KEYFRAME_TYPE_OBSTACLE_BOTTOM) {
          while (_animateObstacleSegments_finished < _animateObstacleSegments_received) {};

          for(int i = 0; i < currentFrame.size; i++) {
            *ObstacleBottomSegments[i] = createObstacleByPos(&imageLayer, POSITION_BOTTOM);
            ObstacleBottomSegments[i]->x = 1900 + i * 200;
            ObstacleBottomSegments[i]->image->isShown = true;
          }
          ObstacleSegmentPointer = &ObstacleBottomSegments;

          // 각종 플래그 초기화
          _animateObstacleSegments_finished = 0;
          _animateObstacleSegments_shown = 0;
          _animateObstacleSegments_received = currentFrame.size;

          _beginthread(animateObstacleSegments, 0, (AnimateProps*) &animateProps);
          while (_animateObstacleSegments_shown < currentFrame.size) {};
        }

        // 위쪽에 있는 장애물 키프레임 렌더링
        else if (currentFrame.type == KEYFRAME_TYPE_OBSTACLE_TOP) {
          while (_animateObstacleSegments_finished < _animateObstacleSegments_received) {};

          for(int i = 0; i < currentFrame.size; i++) {
            *ObstacleTopSegments[i] = createObstacleByPos(&imageLayer, POSITION_TOP);
            ObstacleTopSegments[i]->x = 1900 + i * 200;
            ObstacleTopSegments[i]->image->isShown = true;
          }
          ObstacleSegmentPointer = &ObstacleTopSegments;

          // 각종 플래그 초기화
          _animateObstacleSegments_finished = 0;
          _animateObstacleSegments_shown = 0;
          _animateObstacleSegments_received = currentFrame.size;

          _beginthread(animateObstacleSegments, 0, (AnimateProps*) &animateProps);
          while (_animateObstacleSegments_shown < currentFrame.size) {};
        }

        // 아이템 키프레임 렌더링 -> 이건 효과별로 따로 줘야 하니까 이따 생각
        else if (currentFrame.type == KEYFRAME_TYPE_ITEM) {
          while (_animateItemSegments_finished < _animateItemSegments_received) {};

          for (int i = 0; i < currentFrame.size; i++) {
            *ItemSegments[i] = createItemByType(&imageLayer, currentFrame.effect);
            ItemSegments[i]->x = 1900 + i * 200;
            ItemSegments[i]->image->isShown = true;
          }
          ItemSegmentPointer = &ItemSegments;

          _animateItemSegments_finished = 0;
          _animateItemSegments_shown = 0;
          _animateItemSegments_received = currentFrame.size;

          _beginthread(animateItemSegments, 0, (AnimateProps*) &animateProps);
          while (_animateItemSegments_shown < currentFrame.size) {};
        }

        // 죽었나 HP 체크하고, 드디어 죽었으면 루프 탈출
        if (LIFE.hp < 0.0) {
          isDead = true;

          // 애니메이션 기다려야 함
          break;
        }
        gotoxy(0,0);
        printf("[%d]", LIFE.hp);
      }

      // 프레임 넘어가거나 죽기 전에 애니메이션 다 종료될 때까지 기다려야 함
      while (
        _animateFishSegments_finished < _animateFishSegments_received ||
        _animateObstacleSegments_finished < _animateObstacleSegments_received ||
        _animateItemSegments_finished < _animateItemSegments_received
      ) {};
      // _animateFishSegments_finished = _animateFishSegments_received;
      // _animateFishSegments_shown = _animateFishSegments_received;
      // _animateObstacleSegments_finished = _animateObstacleSegments_received;
      // _animateObstacleSegments_shown = _animateObstacleSegments_received;
      // _animateItemSegments_finished = _animateItemSegments_received;
      // _animateItemSegments_shown = _animateItemSegments_received;
      if (isDead)
        break;
    }
    cat.isRunning = false;

    // isDead 플래그가 설정되어 있다면 사고사,
    // 설정되어 있지 않다면 자연사
    // TODO: isDead 값에 따라 다른 애니메이션 넣기

    // 게임 오버 페이지
    exit(0);
    {
      // 레이어별 이미지를 세팅합니다.
      images[0] = (Image) { .fileName = RESOURCE_BACKGROUND_RESULT, .x = 0, .y = 0, .scale = 1, .isShown = true };
      for (int i = 1; i < 5; i++) {
        images[i].isShown = false;
      }

      // 점수 카운터를 그립니다.
      for (int idx = 5; idx < 11; idx++) {
        images[idx].fileName = RESOURCE_NUMBERS[0];
        images[idx].x = 1565 - idx * 85;
        images[idx].y = 450;
        images[idx].isShown = true;
        images[idx].scale = 1.4;
      }
      images[11] = (Image) { .fileName = RESOURCE_TEXT_RETRY, .x = 700, .y = 750, .scale = 0.9, .isShown = true };
      imageLayer.imageCount = 12;

      // 게임 오버 화면을 보여주기 좋게 윈도우 사이즈를 재조정하고, 렌더링합니다.
      resizeConsole(SCREEN_HEIGHT + 2, SCREEN_WIDTH);
      SCORE.update(&SCORE, 0); // 점수를 표시합니다.
      imageLayer.renderAll(&imageLayer);

      // 현재 점수를 저장합니다.
      // SCORE.save에서 내부적으로 최고 점수보다 높은지를 확인하고, 높은 경우에만 현재 점수를 갱신해 저장합니다.
      SCORE.save(&SCORE, "data.dat");
      while (1) {
        mouse.updatePosition(&mouse);

        // 다시하기 버튼을 눌렀을 경우에만 계속합니다.
        if (mouse.isClicked() && mouse.y >= 380) {
          break;
        }
      }
    }

    // 메모리 할당을 해제합니다.
    for (int i = 0; i < 5; i++) {
      free(fishSegments[i]);
      free(ObstacleBottomSegments[i]);
      free(ObstacleTopSegments[i]);
      free(ItemSegments[i]);
      free(stages[i]);
    }
    free(images);
    firstRun = false;
  }
}
