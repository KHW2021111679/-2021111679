#define POT A1
#define BUTTON 2

int led[] = {11, 5, 3};
int led2[] = {12, 8, 7, 6};
String name[] = {"빨강", "초록", "파랑"};
String eng[] = {"RED", "GREEN", "BLUE"};

unsigned long time = 0;
unsigned long preTime = 0;

int bitValue = 0;
int gameBits = 0;
int gameState = -1;
bool debug = true;

void setup() {
  pinMode(POT, INPUT);
  pinMode(BUTTON, INPUT);

  for (int i = 0; i < 3; i++) {
    pinMode(led[i], OUTPUT);
  }

  for (int i = 0; i < 4; i++) {
    pinMode(led2[i], OUTPUT);
  }

  updateRGB();
  updateLED();

  Serial.begin(9600);
  Serial.setTimeout(100);
  Serial.println("<동작> <LED번호> 입력");
  Serial.println("LED번호: 0~3");
  Serial.println("on / off / change");
}

void loop() {
  while (Serial.available()) {
    readSerial();
  }

  int value = analogRead(POT);
  int color = getColor(value);

  time = millis();
  check(value, color);

  delay(100);
}

void readSerial() {
  int first = Serial.peek();

  if (first == '\r' || first == '\n') {
    Serial.read();
    return;
  }

  if (first >= '0' && first <= '9') {
    long state = Serial.parseInt();
    long charge = Serial.parseInt();
    int end = Serial.read();

    if (end == '\r') {
      end = Serial.read();
    }

    if (end != '\n' || state < 0 || state > 2 || charge < 0 || charge > 4) {
      if (debug) {
        Serial.println("RX: 잘못된 게임 데이터");
      }

      return;
    }

    gameState = state;
    gameBits = (1 << charge) - 1;

    updateRGB();
    updateLED();

    if (debug) {
      Serial.print("RX ");
      Serial.print(state);
      Serial.print(" ");
      Serial.println(charge);
    }

    return;
  }

  String cmd = Serial.readStringUntil(' ');

  if (cmd != "on" && cmd != "off" && cmd != "change") {
    Serial.readStringUntil('\n');
    return;
  }

  long num = Serial.parseInt();
  Serial.readStringUntil('\n');

  if (num < 0 || num > 3) {
    return;
  }

  int bit = 1 << num;

  if (cmd == "on") {
    bitValue = bitValue | bit;
  } else if (cmd == "off") {
    bitValue = bitValue & ~bit;
  } else {
    bitValue = bitValue ^ bit;
  }

  updateLED();

  Serial.print("LED 상태: ");
  Serial.println(bitValue | gameBits, BIN);
}

int getColor(int value) {
  switch (value / 342) {
    case 0:
      return 0;
    case 1:
      return 1;
    default:
      return 2;
  }
}

void show(int value, int color) {
  Serial.print("time: ");
  Serial.print(time);
  Serial.print(" / preTime: ");
  Serial.print(preTime);
  Serial.print(" / 입력: ");
  Serial.print(value);
  Serial.print(" / 색: ");
  Serial.println(name[color]);
}

void check(int value, int color) {
  unsigned long bTime = time - preTime;

  if (digitalRead(BUTTON) == 0 && bTime >= 500) {
    show(value, color);
    preTime = time;

    Serial.print("색상: ");
    Serial.println(eng[color]);
    Serial.print("걸린시간: ");
    Serial.print(bTime);
    Serial.println(" ms");

    blink(color, 5);
    delay(1000);
  }
}

void blink(int color, int num) {
  for (int i = 0; i < 3; i++) {
    digitalWrite(led[i], 0);
  }

  for (int i = 0; i < num; i++) {
    digitalWrite(led[color], 1);
    digitalWrite(led2[color], 1);
    delay(50);

    digitalWrite(led[color], 0);
    digitalWrite(led2[color], 0);
    delay(50);
  }

  updateRGB();
  updateLED();
}

void updateRGB() {
  digitalWrite(led[0], gameState == 2);
  digitalWrite(led[1], gameState == 1);
  digitalWrite(led[2], gameState == 0);
}

void updateLED() {
  int bits = bitValue | gameBits;

  for (int i = 0; i < 4; i++) {
    if (bits & (1 << i)) {
      digitalWrite(led2[i], 1);
    } else {
      digitalWrite(led2[i], 0);
    }
  }
}