let playerX = 350; //플레이어 X
let playerY = 885; //플레이어 Y
let playerSize = 30; //플레이어 크기
let playerColor; //플레이어 색
let colorNum = 1; //색 번호
let playerSpeed = 5; //이동 속도

let enemyX = 350; //적 X
let enemyY = 100; //적 Y
let rad = 0; //좌우 이동 각도
let ang = 0; //회전 각도

let poopX = []; //투사체 X 배열
let poopY = []; //투사체 Y 배열
let poopSpeed = []; //낙하 속도 배열

let gameState = 0; //게임 상태(0,1,2로 상태 조절)
let startTime = 0; //시작 시간
let score = 0; //점수

function setup() {
  createCanvas(700, 1000); //화면 크기
  textAlign(CENTER, CENTER); //중앙 정렬
}

function draw() {
  background(210); //배경 초기화

  strokeWeight(5); //선 두께
  stroke(255, 0, 0); //빨강
  line(50, 100, 650, 100); //위쪽 선

  stroke(0, 255, 0); //초록
  line(50, 900, 650, 900); //아래쪽 선

  stroke(0); //검정 테두리
  strokeWeight(1); //테두리 두께

  switch (
    colorNum //플레이어 색 선택
  ) {
    case 1:
      playerColor = color(255, 0, 0); //빨강
      break;
    case 2:
      playerColor = color(0, 255, 0); //초록
      break;
    case 3:
      playerColor = color(0, 0, 255); //파랑
      break;
  }

  if (gameState == 0) {
    drawPlayer(playerX, playerY); //플레이어

    fill(0); //글자 색
    textSize(30); //글자 크기
    text("똥 피하기\n\n1: 빨강  2: 초록  3: 파랑\nENTER를 눌러 시작", 350, 420);

    textSize(20);
    text("좌우 방향키: 이동 / 마우스 누르기: 느리게", 350, 570); //조작 안내
  } else if (gameState == 1) {
    //게임 진행
    score = int((millis() - startTime) / 1000); //생존 시간

    fill(0); //점수 색
    textSize(25); //점수 크기
    text("Score: " + score, 350, 40); //점수 표시

    if (mouseIsPressed) {
      //마우스 누르는 동안
      playerSpeed = 2; //느린 이동
    } else {
      playerSpeed = 5; //기본 이동
    }

    if (keyIsDown("ArrowLeft")) {
      //왼쪽 방향키
      playerX -= playerSpeed; //왼쪽 이동
    } else if (keyIsDown("ArrowRight")) {
      //오른쪽 방향키
      playerX += playerSpeed; //오른쪽 이동
    }

    playerX = constrain(playerX, 50, 650 - playerSize); //이동 제한
    drawPlayer(playerX, playerY); //플레이어 표시

    enemyX = 350 + sin(rad) * 270; //적 좌우 이동
    rad += 0.05; //이동 각도 증가

    fill(0); //적 색
    ellipse(enemyX, enemyY, 40, 40); //적 표시

    let circleX = enemyX + cos(ang) * 40; //회전 X
    let circleY = enemyY + sin(ang) * 40; //회전 Y

    fill(100); //회전하는 원 색
    ellipse(circleX, circleY, 20, 20); //회전하는 원
    ang += 0.05; //회전 각도 증가

    fill(120, 70, 30); //똥 색

    for (let i = 0; i < poopX.length; i++) {
      //투사체 반복문
      poopY[i] += poopSpeed[i]; //투사체 속도

      if (poopY[i] > 930) {
        //투사체 Y좌표가 930 이상이면
        poopX[i] = enemyX; //적 X에서 재생성
        poopY[i] = enemyY + 20; //시작 높이
        poopSpeed[i] = random(3, 6); //속도 재설정
      }

      ellipse(poopX[i], poopY[i], 20, 20); //투사체 생성

      if (checkCollision(playerX, playerY, poopX[i], poopY[i])) {
        gameState = 2; //충돌 시 종료
        break; //반복 종료
      }
    }
  } else {
    //종료 화면
    drawPlayer(playerX, playerY); //플레이어 표시

    fill(0); //글자 색
    textSize(80); //종료 글자 크기
    text("끝", 350, 300); //종료 표시

    textSize(25); //안내 크기
    text("점수: " + score + "\n마우스를 눌러 다시 시작", 350, 550);
  }

  stroke(0); //마우스 원 테두리
  strokeWeight(1); //테두리 두께

  if (mouseIsPressed) {
    //마우스 클릭 상태
    fill(255, 220, 0); //노란색
  } else {
    fill(255); //흰색
  }

  ellipse(mouseX, mouseY, 12, 12); //마우스 따라가는 원
}

function drawPlayer(x, y) {
  stroke(0); //몸통 테두리
  strokeWeight(1); //테두리 두께
  fill(playerColor); //선택한 색
  rect(x, y, playerSize, playerSize); //몸통

  fill(0);
  ellipse(x + 10, y + 8, 5, 5); //왼쪽 눈
  ellipse(x + 20, y + 8, 5, 5); //오른쪽 눈
  arc(x + 15, y + 15, 25, 15, 0, PI); //입
}

function checkCollision(px, py, bx, by) {
  let x = constrain(bx, px, px + playerSize); //가장 가까운 X
  let y = constrain(by, py, py + playerSize); //가장 가까운 Y

  return dist(x, y, bx, by) <= 10; //똥 반지름과 비교
}

function startGame() {
  //게임 초기화
  playerX = 350; //플레이어 위치
  enemyX = 350; //적 위치
  rad = 0; //이동 각도
  ang = 0; //회전 각도
  score = 0; //점수

  for (let i = 0; i < 10; i++) {
    //투사체 10개 초기화
    poopX[i] = enemyX; //시작 X
    poopY[i] = enemyY + 20; //시작 Y
    poopSpeed[i] = random(3, 6); //랜덤 속도
  }

  startTime = millis(); //시작 시간 저장
  gameState = 1; //게임 진행
}

function keyPressed() {
  if (gameState == 0) {
    //시작 화면
    if (key == "1") {
      colorNum = 1; //빨강
    } else if (key == "2") {
      colorNum = 2; //초록
    } else if (key == "3") {
      colorNum = 3; //파랑
    }

    if (key == "Enter") {
      startGame(); //게임 시작
    }
  }

  if (key == "ArrowLeft" || key == "ArrowRight") {
    return false; //방향키 기본 동작 방지
  }
}

function mousePressed() {
  //마우스 이벤트
  if (gameState == 2) {
    //종료 상태
    startGame(); //재시작
  }
}
