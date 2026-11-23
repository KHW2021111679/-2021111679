#define POT A1
#define POT2 A2
#define BUTTON 2

void setup() {
  pinMode(POT, INPUT);
  pinMode(POT2, INPUT);
  pinMode(BUTTON, INPUT);

  Serial.begin(9600);

  while (Serial.available() == 0) {
    Serial.println('A');
    delay(300);
  }
}

void loop() {
}

void serialEvent() {
  int signal = Serial.read();

  int value = analogRead(POT);
  int value2 = analogRead(POT2);
  int button = digitalRead(BUTTON);

  Serial.print(value);
  Serial.print(",");
  Serial.print(value2);
  Serial.print(",");
  Serial.println(button);
}