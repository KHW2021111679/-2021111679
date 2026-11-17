#define POT A1
#define POT2 A2
#define BUTTON 2

int pre = 1;

void setup() {
  pinMode(POT, INPUT);
  pinMode(POT2, INPUT);
  pinMode(BUTTON, INPUT);
  Serial.begin(9600);
}

void loop() {
  int value = analogRead(POT);
  int value2 = analogRead(POT2);
  int button = digitalRead(BUTTON);

  Serial.print(value);
  Serial.print(",");
  Serial.print(value2);
  Serial.print(",");

  if (button == 0 && pre == 1) {
    Serial.println("YES");
  } else {
    Serial.println("NO");
  }

  pre = button;
  delay(30);
}