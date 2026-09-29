// 부저음 울리기

#define BUZZER 13

void setup() {
  pinMode(BUZZER, OUTPUT);
  tone(BUZZER, 262, 500);    // “도”
  delay(1000);
  noTone(BUZZER);            // 무음
  delay(1000);
  tone(BUZZER, 330, 500);    // “미”
  delay(1000);
  tone(BUZZER, 392, 500);    // “솔”
  delay(1000);
}

void loop() {
}
