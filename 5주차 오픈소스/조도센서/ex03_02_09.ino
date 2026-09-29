// 조도센서값 읽고 출력

#define LIGHT A3

void setup() {
  pinMode(LIGHT, INPUT);
  Serial.begin(9600);
}

void loop() {
  int value = analogRead(LIGHT);
  Serial.print("Light: ");
  Serial.println(value);
  delay(100);
}
