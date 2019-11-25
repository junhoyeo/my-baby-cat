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
  bool firstRun = true;
  updateResources();

  Mouse mouse = DEFAULT_MOUSE;

  ImageLayer imageLayer = DEFAULT_IMAGE_LAYER;
  Image *images = malloc(20 * sizeof(Image));
  imageLayer.initialize(&imageLayer);

  PlaySound(RESOURCE_SOUND_BGM_1, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
  initWindow();

  while (1) {
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
    Sleep(100);

    renderLobby(&imageLayer, &mouse, (firstRun) ? true : false);

    CONSOLE_WIDTH = 120;
    CONSOLE_HEIGHT = 30;
    resizeConsole(SCREEN_HEIGHT, SCREEN_WIDTH);

    images[0] = (Image) { .fileName = RESOURCE_BACKGROUND[0], .x = 0, .y = 0, .scale = 1, .isShown = true };
    images[1] = (Image) { .fileName = RESOURCE_CAT[0], .x = 0, .y = 450, .scale = 1, .isShown = true };
    images[2] = (Image) { .fileName = RESOURCE_LIFE[20], .x = 0, .y = 0, .scale = 1, .isShown = true };
    images[3] = (Image) { .fileName = RESOURCE_EFFECT[0], .x = -50, .y = 100, .scale = 0.9, .isShown = false };
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

    // init cat
    Cat cat = DEFAULT_CAT;
    cat.image = &images[1];
    cat.imageLayer = &imageLayer;
    cat.init(&cat);

    // set LIFE
    LIFE.image = &images[2];
    LIFE.imageLayer = &imageLayer;

    // set SCORE
    for (int idx = 5; idx < 11; idx++) {
      SCORE.images[idx - 5] = &images[idx];
      // printf("%s\n", SCORE.images[idx]->fileName);
    }
    SCORE.imageLayer = &imageLayer;

    // game start
    imageLayer.renderAll(&imageLayer);

    SPEED.addBackgroundThread(&SPEED, SPEED.init);

    cat.addBackgroundThread(&cat, cat.run);
    cat.addBackgroundThread(&cat, cat.listenKeys);
    // fish.addBackgroundThread(&fish, fish.move);

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

    for (int i = 0; i < 5; i++) {
      fishSegments[i] = malloc(sizeof(Fish));
      *fishSegments[i] = createFish(1900 + i * 200);

      ObstacleBottomSegments[i] = malloc(sizeof(Obstacle));

      ObstacleTopSegments[i] = malloc(sizeof(Obstacle));

      ItemSegments[i] = malloc(sizeof(Item));
    }

    double isDead = false;
    for (int key = 0; key < 1; key++) {
      Stage *currentStage = stages[key];

      // 타이틀 보여주기
      currentStage->addBackgroundThread(currentStage, currentStage->render);

      // 배경 바꾸기
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
              images[imageLayer.imageCount] = (Image) { .fileName = RESOURCE_FISH[0], .x = 1900, .y = 600, .scale = 1, .isShown = true };
              fishSegments[i]->image = &images[imageLayer.imageCount];
              fishSegments[i]->imageLayer = &imageLayer;
              imageLayer.imageCount++;
            }
            fishSegments[i]->image->isShown = true;
            fishSegments[i]->init(fishSegments[i]);
          }

          fishSegmentPointer = &fishSegments;

          // 각종 플래그 초기화
          _animateFishSegments_finished = 0;
          _animateFishSegments_shown = 0;
          _animateFishSegments_received = currentFrame.size;

          // 백그라운드 쓰레드를 만들어서 배경에서 움직이게 함
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
      }

      while (
        _animateFishSegments_finished < _animateFishSegments_received ||
        _animateObstacleSegments_finished < _animateObstacleSegments_received ||
        _animateItemSegments_finished < _animateItemSegments_received
      ) {};
      // 프레임 넘어가거나 죽기 전에 애니메이션 다 종료될 때까지 기다려야 함
      if (isDead)
        break;
    }
    cat.isRunning = false;

    // isDead 플래그가 설정되어 있다면 사고사,
    // 설정되어 있지 않다면 자연사
    // TODO: isDead 값에 따라 다른 애니메이션 넣기

    // 게임 오버 페이지
    {
      images[0] = (Image) { .fileName = RESOURCE_BACKGROUND_RESULT, .x = 0, .y = 0, .scale = 1, .isShown = true };
      for (int i = 1; i < 5; i++) {
        images[i].isShown = false;
      }
      for (int idx = 5; idx < 11; idx++) {
        images[idx].fileName = RESOURCE_NUMBERS[0];
        images[idx].x = 1565 - idx * 85;
        images[idx].y = 450;
        images[idx].isShown = true;
        images[idx].scale = 1.4;
      }
      images[11] = (Image) { .fileName = RESOURCE_TEXT_RETRY, .x = 700, .y = 750, .scale = 0.9, .isShown = true };
      imageLayer.imageCount = 12;
      SCORE.update(&SCORE, 0); // 점수 표시
      resizeConsole(SCREEN_HEIGHT + 2, SCREEN_WIDTH);
      imageLayer.renderAll(&imageLayer);

      SCORE.save(&SCORE, "data.dat");
      Sleep(2000);
      // while (1) {};
    }

    for (int i = 0; i < 5; i++) {
      free(fishSegments[i]);
      free(ObstacleBottomSegments[i]);
      free(ObstacleTopSegments[i]);
      free(ItemSegments[i]);
      free(stages[i]);
    }
    firstRun = false;
  }
}
