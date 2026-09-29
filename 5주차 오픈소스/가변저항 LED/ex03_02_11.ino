// 가변저항으로 LED 점멸시간 제어

#define VARIABLE_R A1
#define LED 6

void setup() {
  pinMode(VARIABLE_R, INPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int value = analogRead(VARIABLE_R);
  int time = map(value, 0, 1023, 100, 1000);
  digitalWrite(LED, 1);
  delay(time);
  digitalWrite(LED, 0);
  delay(time);
  Serial.print("On_Off Time: ");
  Serial.println(value);
}
