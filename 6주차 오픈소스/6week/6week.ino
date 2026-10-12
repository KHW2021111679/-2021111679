#define POT A1
#define BUTTON 2

int led[] = {11, 5, 3}; //RGB
String name[] = {"빨강", "초록", "파랑"};
String eng[] = {"RED", "GREEN", "BLUE"};

unsigned long time = 0;
unsigned long preTime = 0;

void setup() {
  pinMode(POT, INPUT);
  pinMode(BUTTON, INPUT);

  for (int i = 0; i < 3; i++) { //배열 
    pinMode(led[i], OUTPUT);
  }

  Serial.begin(9600);
}

void loop() {
  int value = analogRead(POT);
  int color = getColor(value);

  time = millis();
  show(value, color);
  check(color);

  delay(100);
}

int getColor(int value) { //색
  if (value < 342) {
    return 0;
  } else if (value < 684) {
    return 1;
  } else {
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

void check(int color) { //버튼 처리
  unsigned long bTime = time - preTime; //걸린시간

  if (digitalRead(BUTTON) == 0 && bTime >= 500) {
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
    delay(50);
    digitalWrite(led[color], 0);
    delay(50);
  }
}