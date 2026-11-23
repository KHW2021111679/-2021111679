let port;
let value = 512;
let value2 = 0;
let button = 1;
let pre = 1;
let msg = "수신 대기";

let playerX = 350;
let playerY = 885;
let playerSize = 30;

let enemyX = 350;
let enemyY = 100;
let ang = 0;

let poopX = [];
let poopY = [];
let poopSpeed = [];

let gameState = 0;
let startTime = 0;
let score = 0;

function setup() {
  createCanvas(700, 1000);
  textAlign(CENTER, CENTER);

  port = new p5.WebSerial();
  port.on("portavailable", openPort);
  port.on("data", serialEvent);

  let btn = createButton("포트 연결");
  btn.mousePressed(choosePort);
}

function draw() {
  background(210);

  strokeWeight(3);
  stroke(255, 0, 0);
  line(50, 100, 650, 100);

  stroke(0, 180, 0);
  line(50, 900, 650, 900);

  stroke(0);
  strokeWeight(1);

  playerX = map(value, 0, 1023, 50, 650 - playerSize);
  playerX = constrain(playerX, 50, 650 - playerSize);

  if (gameState == 0) {
    fill(0);
    textSize(30);
    text("똥 피하기", 350, 350);

    textSize(23);
    text(
      "포트 연결 후 버튼을 눌러 시작\n가변저항 1: 좌우 이동\n가변저항 2: 색 변경",
      350,
      470
    );
  } else if (gameState == 1) {
    playGame();
  } else {
    fill(0);
    textSize(60);
    text("끝", 350, 350);

    textSize(25);
    text("점수: " + score + "\n버튼을 눌러 다시 시작", 350, 500);
  }

  drawPlayer(playerX, playerY);

  fill(0);
  textSize(20);
  text("수신: " + msg, 350, 160);
  text("버튼: " + button, 350, 195);
  text("게임 상태: " + gameState, 350, 230);
}

function playGame() {
  score = int((millis() - startTime) / 1000);

  fill(0);
  textSize(25);
  text("Score: " + score, 350, 40);

  enemyX = 350 + sin(ang) * 270;
  ang += 0.05;

  fill(0);
  ellipse(enemyX, enemyY, 40, 40);

  fill(120, 70, 30);

  for (let i = 0; i < poopX.length; i++) {
    poopY[i] += poopSpeed[i];

    if (poopY[i] > 930) {
      poopX[i] = enemyX;
      poopY[i] = enemyY + 20;
      poopSpeed[i] = random(3, 6);
    }

    ellipse(poopX[i], poopY[i], 20, 20);

    if (checkCollision(playerX, playerY, poopX[i], poopY[i])) {
      gameState = 2;
      break;
    }
  }
}

function drawPlayer(x, y) {
  let colorNum = int(value2 / 342);

  switch (colorNum) {
    case 0:
      fill(255, 0, 0);
      break;
    case 1:
      fill(0, 255, 0);
      break;
    case 2:
      fill(0, 0, 255);
      break;
  }

  rect(x, y, playerSize, playerSize);

  fill(0);
  ellipse(x + 10, y + 8, 5, 5);
  ellipse(x + 20, y + 8, 5, 5);
  arc(x + 15, y + 15, 25, 15, 0, PI);
}

function checkCollision(px, py, bx, by) {
  let x = constrain(bx, px, px + playerSize);
  let y = constrain(by, py, py + playerSize);

  return dist(x, y, bx, by) <= 10;
}

function startGame() {
  enemyX = 350;
  ang = 0;
  score = 0;

  for (let i = 0; i < 10; i++) {
    poopX[i] = enemyX;
    poopY[i] = enemyY + 20;
    poopSpeed[i] = random(3, 6);
  }

  startTime = millis();
  gameState = 1;
}

function serialEvent() {
  let str = port.readLine();

  if (!str) {
    return;
  }

  msg = str.trim();

  let data = msg.split(",");

  port.write("B");

  if (data.length != 3) {
    return;
  }

  value = int(data[0]);
  value2 = int(data[1]);
  button = int(data[2]);

  if (button == 0 && pre == 1) {
    if (gameState != 1) {
      startGame();
    }
  }

  pre = button;
}

function choosePort() {
  port.requestPort();
}

function openPort() {
  port.open({ baudRate: 9600 });
}