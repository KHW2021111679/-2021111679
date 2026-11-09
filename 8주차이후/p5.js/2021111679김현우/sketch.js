let port;
let sendTime = 0;
let debug = true;

let playerX = 350;
let playerY = 885;
let playerSize = 30;
let playerColor;
let colorNum = 1;
let playerSpeed = 5;

let enemyX = 350;
let enemyY = 100;
let rad = 0;
let ang = 0;

let poopX = [];
let poopY = [];
let poopSpeed = [];

let gameState = 0;
let startTime = 0;
let score = 0;

let charge = 0;
let lastStep = 0;

function setup() {
  createCanvas(700, 1000);
  textAlign(CENTER, CENTER);

  port = new p5.WebSerial();
  port.on("portavailable", openPort);
  port.on("openerror", showSerialError);
  port.on("writeerror", showSerialError);
  port.on("data", readBoard);

  let button = createButton("아두이노 포트 연결");
  button.position(20, 15);
  button.mousePressed(choosePort);
}

function draw() {
  background(210);

  strokeWeight(5);
  stroke(255, 0, 0);
  line(50, 100, 650, 100);

  stroke(0, 255, 0);
  line(50, 900, 650, 900);

  stroke(0);
  strokeWeight(1);

  switch (colorNum) {
    case 1:
      playerColor = color(255, 0, 0);
      break;
    case 2:
      playerColor = color(0, 255, 0);
      break;
    case 3:
      playerColor = color(0, 0, 255);
      break;
  }

  if (gameState == 0) {
    drawPlayer(playerX, playerY);

    fill(0);
    textSize(30);
    text(
      "똥 피하기\n\n1: 빨강  2: 초록  3: 파랑\nENTER를 눌러 시작",
      350,
      420
    );

    textSize(20);
    text("좌우 방향키: 이동 / 마우스 누르기: 느리게", 350, 570);
  } else if (gameState == 1) {
    score = int((millis() - startTime) / 1000);
    updateCharge();

    fill(0);
    textSize(25);
    text("Score: " + score, 350, 40);
    text("충전: " + charge + " / 4", 350, 70);

    if (mouseIsPressed) {
      playerSpeed = 2;
    } else {
      playerSpeed = 5;
    }

    if (keyIsDown("ArrowLeft")) {
      playerX -= playerSpeed;
    } else if (keyIsDown("ArrowRight")) {
      playerX += playerSpeed;
    }

    playerX = constrain(playerX, 50, 650 - playerSize);
    drawPlayer(playerX, playerY);

    enemyX = 350 + sin(rad) * 270;
    rad += 0.05;

    fill(0);
    ellipse(enemyX, enemyY, 40, 40);

    let circleX = enemyX + cos(ang) * 40;
    let circleY = enemyY + sin(ang) * 40;

    fill(100);
    ellipse(circleX, circleY, 20, 20);
    ang += 0.05;

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
  } else {
    drawPlayer(playerX, playerY);

    fill(0);
    textSize(80);
    text("끝", 350, 300);

    textSize(25);
    text("점수: " + score + "\n마우스를 눌러 다시 시작", 350, 550);
  }

  stroke(0);
  strokeWeight(1);

  if (mouseIsPressed) {
    fill(255, 220, 0);
  } else {
    fill(255);
  }

  ellipse(mouseX, mouseY, 12, 12);
  sendGame();
}

function updateCharge() {
  let chargeStep = int(score / 10);

  if (chargeStep > lastStep) {
    charge = min(4, charge + chargeStep - lastStep);
    lastStep = chargeStep;
  }
}

function drawPlayer(x, y) {
  stroke(0);
  strokeWeight(1);
  fill(playerColor);
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
  playerX = 350;
  enemyX = 350;
  rad = 0;
  ang = 0;
  score = 0;
  charge = 0;
  lastStep = 0;

  for (let i = 0; i < 10; i++) {
    poopX[i] = enemyX;
    poopY[i] = enemyY + 20;
    poopSpeed[i] = random(3, 6);
  }

  startTime = millis();
  gameState = 1;
}

function keyPressed() {
  if (gameState == 0) {
    if (key == "1") {
      colorNum = 1;
    } else if (key == "2") {
      colorNum = 2;
    } else if (key == "3") {
      colorNum = 3;
    }

    if (key == "Enter") {
      startGame();
    }
  }

  if (key == "ArrowLeft" || key == "ArrowRight") {
    return false;
  }
}

function mousePressed(event) {
  if (gameState == 2 && event.target.tagName == "CANVAS") {
    startGame();
  }
}

function choosePort() {
  if (!port.portOpen) {
    port.requestPort();
  }
}

function openPort() {
  port.open({ baudRate: 9600 });
}

function sendGame() {
  if (port.portOpen && millis() - sendTime >= 200) {
    if (debug) {
      console.log("TX", gameState, charge);
    }

    port.write(gameState + " " + charge + "\n");
    sendTime = millis();
  }
}

function readBoard() {
  let line = port.readStringUntil("\n");

  while (line != null) {
    if (debug) {
      console.log(line);
    }

    line = port.readStringUntil("\n");
  }
}

function showSerialError(error) {
  console.log(error);
}