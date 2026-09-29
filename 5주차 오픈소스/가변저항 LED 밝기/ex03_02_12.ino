// 가변저항으로 LED 밝기 조절

#define VARIABLE_R A1
#define LED 6

void setup() {
  pinMode(VARIABLE_R, INPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int value = analogRead(VARIABLE_R);
  int brightness = map(value, 0, 1023, 0, 255);
  analogWrite(LED, brightness);
  Serial.print("Brightness: ");
  Serial.println(brightness);
  delay(100);
}
