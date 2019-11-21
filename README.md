# 마이 베이비 캣
- 사실상 11월 18일부터 시작합니다.
- 그런데 22일 11시까지 제출입니다.
- 제 인생은 레전드입니다.
- 게임 설명서는 늦어도 목요일부터는 작성해 나가야 합니다.
- 이미지를 포함한 모든 파일은 `Main.c`가 위치한 프로젝트 루트에서부터 절대경로로 참조됩니다. 이는 설명서에 명시되어야 합니다.
- OS X에서 페러렐즈를 이용해, 가상화된 Windows 환경에서 개발되었으므로 일부 실행 환경에서 오류가 발생할 수 있음 역시 명시해야 합니다.

## 스프린트
- 일단 시간이 촉박하기 때문에 애자일 방법론을 따릅니다.
- 4일 동안 하루라는 이터레이션이 있습니다.
- 이쯤 되면 진짜루 레전드

### 1. 최소기능제품
여기까지 마스터로 커밋 바로 하고, 2번 스프린트부턴 테스트하고 머지할 때까진 새로 판 브랜치에서 합니다.

- [x] 고양이 표시하기
- [x] 고양이 혼자 제자리걸음
- [x] (기본값으로 지정한) 속도에 따라 걷기
- [x] 물고기 표시하기
- [x] 물고기 이동시키기
- [x] 물고기 계속 생성해 나가기
- [x] 물고기 먹었는지(고양이와 접촉) 확인
- [x] 점수 표시하기
- [x] 물고기 먹으면 점수 주기

### 2. 그래도 게임 같게
마감 하루 전에 시작하는 두 번째 스프린트입니다.

- [x] 스페이스 바를 눌러서 점프하기
- [x] 아래 화살표를 누르고 있는 동안 슬라이딩하기
- [ ] 바닥에 있는 장애물 표시하기
- [ ] 바닥에 있는 장애물의 종류를 랜덤으로 하기
- [ ] 위에 있는 장애물 표시하기
- [ ] 장애물 회피 구현하기
- [ ] 장애물 부딪히는 애니메이션 적용하기

### 3. 오늘 밤에 달릴 거야

- [ ] 체력 구현하기
- [ ] 체력 바 표시하기
- [ ] 체력 바 애니메이션 적용하기
- [ ] 아이템 구현하기
- [ ] 아이템 생성하기
- [ ] 아이템 먹었을 때 효과 적용하기

### 4. 내일 새벽에 완성할지도

- [ ] 자동으로 물고기, 장애물, 아이템 생성하기
- [ ] 스테이지 구현
- [ ] 스테이지 넘어가는 거 만들기
- [ ] 재시작 버튼 만들기

### 5. 만약에 시간 남으면

- [ ] 로비 구현하기
- [ ] 구멍 만들기
- [ ] 각종 아이템 따위에 메모리 잡아먹는 애니메이션 적용하기

## 기획

### 레이아웃
- 쿠키런 같은 느낌
- 가로로 긴 스크린
- 고양이는 왼편에 고정됨(속도에 맞춰 제자리걸음)
- 배경/장애물 오른쪽에서 왼쪽으로 움직임
- 슬라이딩, 점프, 죽었을 때 스프라이트 필요

### 조작
- 공룡 게임처럼...
- 스페이스 바 눌러서 점프
- 다운 키 눌러서 슬라이딩
- 아이템은 접촉하면 바로 써짐
- 물고기(?)도 접촉하면 바로 먹는 거임

### 아이템
- 체력 회복
- 속도 감소 or 대시
- 무적
- 물고기(젤리 같은 거임) 당 추가점수

### 기능
- 배경음악 재생
- 메인 화면(로비) 존재
- 죽고선 점수 보여주고 재시작 또는 메인 화면으로 돌아가기
- 최고 점수, 코인, 레벨 등 저장됨
