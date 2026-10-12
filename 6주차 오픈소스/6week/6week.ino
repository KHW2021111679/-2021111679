#define POT A1 //가변저항
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
  int color = value / 342; //색구간

  show(value, color);

  if (check(500)) {
    blink(color);
    delay(1000);
  }

  delay(100);
}

void show(int value, int color) { //시리얼 출력
  Serial.print("입력: ");
  Serial.print(value);
  Serial.print(" / 색: ");
  Serial.println(name[color]);
  
}

int check(int a) { //실행 판단
  time = millis();

  

  if (digitalRead(BUTTON) == 0 && time - preTime >= a) {
    preTime = time;
    return 1;
  }
  return 0;
}

void blink(int color) { //점멸
  Serial.print("색상: ");
  Serial.println(eng[color]);
  
  Serial.print("time:");
  Serial.print(time);
  Serial.print(" / preTime: ");
  Serial.println(preTime);

  for (int i = 0; i < 5; i++) {
    digitalWrite(led[color], 1);
    delay(50);
    digitalWrite(led[color], 0);
    delay(50);
  }
}