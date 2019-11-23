# 마이 베이비 캣
- 이미지를 포함한 모든 파일은 `Main.c`가 위치한 프로젝트 루트에서부터 절대경로로 참조됩니다.
- OS X에서 페러렐즈를 이용해 가상화된 Windows 환경에서 개발했습니다.

## Todo

- [x] 점프 고치기
- [x] 슬라이딩 고치기 및 플래그 추가
- [x] 장애물에 충돌했는지 감지하기
- [ ] 장애물에 충돌하면 속도 줄이기
- [ ] 장애물 충돌시 애니메이션 또는 효과
- [ ] 아이템 먹었을 때 효과 적용하기
- [ ] 스테이지 구현
- [ ] 스테이지 넘어가는 거 만들기
- [ ] 재시작 버튼 만들기
- [ ] 로비 구현하기
- [ ] 최근 전적 저장하기
- [ ] 최고 점수 저장하기
- [ ] 메모리 잡아먹는 애니메이션 적용하기

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
