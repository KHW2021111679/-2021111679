// 가변저항값 읽고 출력하기

#define VARIABLE_R A1

void setup() {
  pinMode(VARIABLE_R, INPUT);
  Serial.begin(9600);
}

void loop() {
  int value = analogRead(VARIABLE_R);
  Serial.print("Variable Resistor: ");
  Serial.println(value);
  delay(100);
}
