// 버튼값 읽고 출력하기

#define BUTTON 2

void setup() {
  pinMode(BUTTON, INPUT);
  Serial.begin(9600);
}

void loop() {
  int value = digitalRead(BUTTON);
  Serial.print("Button: ");
  Serial.println(value);
  delay(100);
}
