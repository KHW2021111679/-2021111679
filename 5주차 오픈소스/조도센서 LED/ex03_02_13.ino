// 어두울수록 LED 밝게 하기

#define LIGHT A3
#define LED 6
#define MIN 100  // 주위의 밝기에 따라 수정 요! (센서를 완전히 가린 상태)
#define MAX 300 // 주위의 밝기에 따라 수정 요! (센서를 가리지 않은 상태)

void setup() {
  pinMode(LIGHT, INPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int value = analogRead(LIGHT);
  Serial.print("LIGHT: ");
  Serial.print(value);
  value = constrain(value, MIN, MAX);
  int brightness = map(value, MIN, MAX, 255, 0);
  analogWrite(LED, brightness);
  Serial.print(" Brightness: ");
  Serial.println(brightness);
  delay(100);
}
