#define POT A1
#define LED 6

void setup() {
  pinMode(POT, INPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int value = analogRead(POT);
  int b = map(value, 0, 1023, 0, 255);

  analogWrite(LED, b);

  Serial.print("입력: ");
  Serial.print(value);
  Serial.print("/ LED 밝기: ");
  Serial.println(b);

  delay(100);
}
