#define POT A1 //가변저항
#define BUTTON 2
#define RED 11
#define GREEN 5
#define BLUE 3

unsigned long preTime = 0;
unsigned long time = 0;

int led = RED;

void setup() {
  pinMode(POT, INPUT);
  pinMode(BUTTON, INPUT);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int value = analogRead(POT); //가변저항값
  int color = value / 342; // 1024나누기3=341.

  switch (color) { //LED색 선택
    case 0:
      led = RED;
      break;
    case 1:
      led = GREEN;
      break;
    case 2:
      led = BLUE;
      break;
  }

  Serial.print("입력: ");
  Serial.println(value);

  time = millis();

  if (digitalRead(BUTTON) == LOW && time - preTime >= 3000) { //버튼 && 3초 지나서 
    preTime = time;

    Serial.print("색상: ");

    switch (color) {
      case 0:
        Serial.println("RED");
        break;
      case 1:
        Serial.println("GREEN");
        break;
      case 2:
        Serial.println("BLUE");
        break;
    }

      for (int i = 0; i < 5; i++) {
        digitalWrite(led, HIGH);
        delay(50);
        digitalWrite(led, LOW);
        delay(50);
     }
    delay(1000); //버튼 누를때 (if) 딜레이
  }

  delay(100); //갱신 딜레이
}
