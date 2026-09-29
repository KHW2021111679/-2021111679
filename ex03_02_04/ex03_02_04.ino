#include <Servo.h>

Servo servo;

void setup() {
  pinMode(2, INPUT);
  pinMode(6, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A5, INPUT);
  servo.attach(A0);
}

void loop() {
  digitalWrite(6, digitalRead(2) == LOW);

  int value = analogRead(A1);
  digitalWrite(11, value < 341);
  digitalWrite(5, value >= 341 && value < 682);
  digitalWrite(3, value >= 682);
  servo.write(map(value, 0, 1023, 0, 180));

  noTone(13);
  tone(13, 440, 100 * (analogRead(A3) < 200) + 1);

  digitalWrite(A4, LOW);
  delayMicroseconds(2);
  digitalWrite(A4, HIGH);
  delayMicroseconds(10);
  digitalWrite(A4, LOW);

  long duration = pulseIn(A5, HIGH, 30000);
  int distance = duration * 0.017;

  digitalWrite(10, LOW);
  digitalWrite(9, duration > 0 && distance < 20);

  delay(100);
}
