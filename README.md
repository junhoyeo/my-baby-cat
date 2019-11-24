# 마이 베이비 캣
- 이미지를 포함한 모든 파일은 `Main.c`가 위치한 프로젝트 루트에서부터 절대경로로 참조됩니다.
- OS X에서 페러렐즈를 이용해 가상화된 Windows 환경에서 개발했습니다.

## Todo

- [x] 스테이지 넘어갈때
- [ ] 죽기
- [x] 점수 저장
- [ ] 점수 보여주기
- [ ] 다시하기
- [x] 아이템 여러개 렌더링
- [x] 아이템 먹었을 때 효과(점수 증/감, 체력 회복)
- [ ] 장애물 위에 꺼 부딪혔을 때 만들기

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
├── Stage.h
├── Utils.h
└── resources
    ├── background
    ├── cat
    ├── fish
    ├── item
    ├── life
    ├── number
    ├── obstacles
    ├── sound
    └── tile
```
