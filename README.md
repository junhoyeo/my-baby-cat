# My Baby Cat

## Structure

```text
.
├── Animate
│   ├── Animate.h
│   ├── AnimateFish.h
│   ├── AnimateItem.h
│   └── AnimateObstacle.h
├── ImageLayer
│   ├── ImageLayer.h
│   ├── ImageLayerImpl.h
│   └── ImageLayerInterface.h
├── Init.h
├── Keyframe
│   ├── Keyframe.h
│   └── KeyframeIntf.h
├── Lobby.h
├── Main.c
├── Mouse
│   ├── Mouse.h
│   ├── MouseImpl.h
│   └── MouseIntf.h
├── MyBabyCat.sln
├── MyBabyCat.vcxproj
├── MyBabyCat.vcxproj.filters
├── MyBabyCat.vcxproj.user
├── Objects
│   ├── Cat
│   │   ├── Cat.h
│   │   ├── CatImpl.h
│   │   └── CatIntf.h
│   ├── Effect
│   │   ├── Effect.h
│   │   ├── EffectImpl.h
│   │   └── EffectIntf.h
│   ├── Fish
│   │   ├── Fish.h
│   │   ├── FishImpl.h
│   │   └── FishIntf.h
│   ├── Item
│   │   ├── Item.h
│   │   ├── ItemImpl.h
│   │   └── ItemIntf.h
│   ├── Life
│   │   ├── Life.h
│   │   ├── LifeImpl.h
│   │   └── LifeIntf.h
│   ├── Obstacle
│   │   ├── Obstacle.h
│   │   ├── ObstacleImpl.h
│   │   └── ObstacleIntf.h
│   └── Score
│       ├── Score.h
│       ├── ScoreImpl.h
│       └── ScoreIntf.h
├── README.md
├── Resources.h
├── Speed.h
├── Stage
│   ├── Stage.h
│   ├── StageFrames.h
│   ├── StageImpl.h
│   └── StageIntf.h
├── Utils.h
├── data.dat
└── resources
    ├── background
    ├── cat
    ├── effect
    ├── fish
    ├── item
    ├── life
    ├── number
    ├── obstacles
    ├── sound
    ├── text
    └── tile
```

## Report

### 게임 개요
My Baby Cat은 앞으로 달려가는 고양이를 조종해 최대한 오래 살아남아 많은 점수를 얻는 게임이다(쿠키런에서 모티브를 얻음). 고양이의 속도는 점점 빨라지고, 이와 동시에 체력 또한 점점 줄어든다. 스페이스 바를 눌러 점프할 수 있고, 방향키(아래)를 눌러 슬라이딩을 할 수 있으며, 이를 통해 장애물을 피할 수 있다. 만약 장애물에 충돌할 시 체력이 줄어들게 된다.
고양이가 생선에 닿으면 점수가 올라가며, 아이템에 닿을 시 체력 회복, 이동 속도 변경 등의 효과가 적용된다. 최대한 많은 생선을 먹어 최고점수를 갱신해 나가는 것이 게임의 목표이고, 쉽고 간단한 조작법, 그래픽으로 모두가 좋아할 만한 게임을 만들기 위해 노력했다. 자세한 게임 문서는 공식 문서 사이트에서 확인할 수 있게 했다.

공식 문서 사이트: http://junhoyeo.github.io/my-baby-cat
프로젝트 깃허브: https://github.com/junhoyeo/my-baby-cat

이미지를 포함한 모든 파일은 `Main.c`가 위치한 프로젝트 루트에서부터 절대경로로 참조된다.
OS X에서 페러렐즈를 이용해 가상화된 Windows 환경에서 개발했다. 일부 환경에서는 메모리 오류 등이 발생하기도 하는 것 같다.

### 새롭게 알게 된 내용

#### 필요했던 계기 및 발생한 문제
고양이 이미지가 일정 간격으로 끊임없이 변하면서 움직여야 달리는 모션을 구현할 수 있었다. 그러면서도 다른 물고기나 아이템 효과, 충돌 효과 등을 나타내야 했기 때문에 동시에 여러 프로세스를 실행시킬 방법을 찾아야 했다.

#### 해결 방법
`process.h`의 `_beginthread` 함수를 사용해서 자식 스레드를 생성할 수 있었다. 실행할 함수의 포인터와 인수 하나를 전달할 수 있어서, `Animate` 폴더 안에 있는 `AnimateFish.h`, `AnimateItem.h`, `AnimateObstacle.h`의 함수들에서처럼 여러 개의 인수를 전달할 때는 이에 맞는 구조체(타입스크립트의 인터페이스 느낌?)를 만든 뒤 이를 전달해 함수 안에서 destructuring을 했다.

### 게임의 기술적 포인트 3가지

1. 해당 게임에서 얻은 점수가 표시되고 나서, `data.dat` 파일을 열고 이전에 기록된 최고 점수와 비교해 신기록일 경우에만 갱신하는데, 사용자의 입장에서 당황할 수 있는 오류를 최소화하고자 `GetFileAttributes` 함수를 이용해 `data.dat` 파일이 없을 경우도 새로운 파일을 생성하도록 유연하게 처리했다.

2. 고양이와 장애물이 충돌했을 때 나타나는 애니메이션이 매우 사실적이다. 총 10장의 효과 프레임을 `Sleep` 함수를 이용해 0.1초 간격으로 렌더링해서 진짜 터지는 듯한 느낌이 든다.

3. 스테이지가 바뀔 때 배경이 바뀌면서 윗부분에 스테이지 이름이 3.5초 동안 나타났다 사라진다. `_beginthread`를 이용해 구현했다.

### 사용한 조건

#### 조건 1

```c
(mouse->isClicked() && mouse->x >= 600 && mouse->y >= 200)
```

게임 타이틀, 로비, 게임 오버 화면 등 버튼이 눌릴 때 다음으로 넘어가는 구현이 필요한 스크린들이 있었다. 무한 루프 반복문 안에 위의 조건이 충족된 경우에만 `break`하는 코드를 작성해, 마우스가 클릭되면서 버튼이 있는 특정 위치에 마우스 포인터가 있을 경우에만 다음 스크린으로 넘어가게 만들었다.

#### 조건 2

```c
self->isRunning
```

백그라운드 스레드로 돌아가면서 고양이를 달리게 하는 `_Cat_run` 함수 안의 `while` 조건에 위의 식을 사용했다. 고양이가 점프를 하거나 슬라이드를 할 때, 돌아가는 스레드를 멈추게 하기 위해서 `isRunning` 속성의 값을 `false`로 만들어서 달리는 것을 멈추게 할 수 있었다.

#### 조건 3

```c
(self->hp > 99)
```

HP에 맞는 생명 표시줄 이미지를 불러오기 위해서 위의 식을 사용했다. 생명 표시줄 이미지는 HP 0, 5, 10, ... 95, 100처럼 5점 간격으로 총 21장이 존재한다. 단순히 `(self->hp / 5)`를 이용해도 되지만, 부동소수점 자료형의 HP가 `99.n`이 되어도 바로 100에서 95로 띄워지는 이미지가 달라져 부자연스러워졌다. 따라서 위 조건을 이용해 삼항연산자를 사용해 `(self->hp > 99) ? 20 : (self->hp / 5)`로 이미지 인덱스를 구했다.

### 음악 재생과 이미지 띄우기 구현 방법

1. `winmm.lib`의 `PlaySound` 함수를 이용해서 배경음악과 물고기/아이템/장애물 충돌 시에 발생하는 효과음 재생을 구현했다.
2. 승현이가 만든 `ImageLayer` 라이브러리를 기반으로 해서 여러 장의 이미지를 레이어 개념으로 표시할 수 있게 했다(DC 구조(Device Context)와 `CreateCompatibleBitmap`, `TransparentBlt` 함수 등 사용). 기존의 `ImageLayer`는 `images` 포인터 배열 안의 이미지를 모두 렌더링했는데, `Image` 구조체 안에 `isShown` 속성을 만들어 그것이 true인 이미지만 표시하도록 수정해서 더욱 유연하게 처리할 수 있도록 했다.

### 느낀 점

- 상윤(그래픽 디자인 및 구조 기획): 다른 조에 비해 늦게 시작해서 우여곡절도 많고 여러모로 아쉬운 부분도 있었지만, 그만큼 다른 조에게 그래픽은 뒤쳐지지 않도록 열심히 노력했다. 준호와 같이 작업하며 정말 즐거웠다. 준호에게 정말 수고했다는 말을 전하고 싶다.

- 준호(게임 개발): 늦게 시작한 만큼 늦게 제출하게 되어 속상했지만, 그만큼 완성도를 높이는 데 시간을 많이 쏟았기 때문에 아깝지는 않았다. 언제 다시 시간이 된다면 메모리 관리 등의 로직을 더 효율적으로 고쳐보고 싶고, 물고기나 아이템, 장애물을 움직이는 함수들을 추상화시키고 싶었다. 자바스크립트 등의 고수준 언어로도 다시 만들어 보고 싶었다. 생각보다 많은 이미지가 사용되었는데, 이걸 하나하나 고생하며 직접 그린 상윤이가 정말 고맙고 멋있었다. 게임 기획에 대한 조언이나 구현에 대한 개선 사항도 계속 피드백을 해줘서 개발하는 데 정말 즐거웠다.
