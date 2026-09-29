#define RedLED 11
#define GreenLED 5
#define BlueLED 3

void setup() {
  pinMode(RedLED, OUTPUT);
  pinMode(GreenLED, OUTPUT);
  pinMode(BlueLED, OUTPUT);
}

void loop() {
  // Red: (R, G, B) = (1, 0, 0)
  digitalWrite(RedLED, 1);
  digitalWrite(GreenLED, 0);
  digitalWrite(BlueLED, 0);
  delay(1000);

  // Green: (R, G, B) = (0, 1, 0)
  digitalWrite(RedLED, 0);
  digitalWrite(GreenLED, 1);
  digitalWrite(BlueLED, 0);
  delay(1000);

  // Blue: (R, G, B) = (0, 0, 1)
  digitalWrite(RedLED, 0);
  digitalWrite(GreenLED, 0);
  digitalWrite(BlueLED, 1);
  delay(1000);
}
