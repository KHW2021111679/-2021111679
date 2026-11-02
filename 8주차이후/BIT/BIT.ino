#define POT A1
#define BUTTON 2

int led[] = {11, 5, 3}; //RGB
int led2[] = {12, 8, 7, 6}; //일반 LED
String name[] = {"빨강", "초록", "파랑"};
String eng[] = {"RED", "GREEN", "BLUE"};

unsigned long time = 0;
unsigned long preTime = 0;
int bitValue = 0; //LED 4개의 비트 상태

void setup() {
  pinMode(POT, INPUT);
  pinMode(BUTTON, INPUT);

  for (int i = 0; i < 3; i++) {
    pinMode(led[i], OUTPUT);
  }

  for (int i = 0; i < 4; i++) {
    pinMode(led2[i], OUTPUT);
  }

  Serial.begin(9600);
  Serial.println("'<LED번호> <동작> ' 입력");
  Serial.println("LED번호: 0~3");
  Serial.println("on / off / change");
}

void loop() {
  if (Serial.available()) {
    String cmd = Serial.readStringUntil(' ');
    int num = Serial.parseInt();

    if (num >= 0 && num < 4) {
      int bit = 1 << num;

      if (cmd == "on") {
        bitValue = bitValue | bit;
      } else if (cmd == "off") {
        bitValue = bitValue & ~bit;
      } else if (cmd == "change") {
        bitValue = bitValue ^ bit;
      }

      if (cmd == "on" || cmd == "off" || cmd == "change") {
        updateLED(); //검사

        Serial.print("LED 상태: ");
        Serial.println(bitValue, BIN); //BINARY로 bitValue
      }
    }
  }

  int value = analogRead(POT);
  int color = getColor(value);

  time = millis();
  check(value, color);

  delay(100);
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

void show(int value, int color) { //출력
  Serial.print("time: ");
  Serial.print(time);
  Serial.print(" / preTime: ");
  Serial.print(preTime);
  Serial.print(" / 입력: ");
  Serial.print(value);
  Serial.print(" / 색: ");
  Serial.println(name[color]);
}

void check(int value, int color) { //버튼 처리
  unsigned long bTime = time - preTime; //걸린시간

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

void blink(int color, int num) { //점멸
  for (int i = 0; i < num; i++) {
    digitalWrite(led[color], 1);
    digitalWrite(led2[color], 1);
    delay(50);

    digitalWrite(led[color], 0);
    digitalWrite(led2[color], 0);
    delay(50);
  }

  updateLED(); //검사
}

void updateLED() { //검사
  for (int i = 0; i < 4; i++) {
    if (bitValue & (1 << i)) {
      digitalWrite(led2[i], 1);
    } else {
      digitalWrite(led2[i], 0);
    }
  }
}
