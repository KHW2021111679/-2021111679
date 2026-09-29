#define DCMOTOR_FWD 9
#define DCMOTOR_BWD 10

void setup() {
  pinMode(DCMOTOR_FWD, OUTPUT);
  pinMode(DCMOTOR_BWD, OUTPUT);
}

void loop() {
  digitalWrite(DCMOTOR_FWD, 1);     // 정방향 회전
  digitalWrite(DCMOTOR_BWD, 0);
  delay(2000);
  digitalWrite(DCMOTOR_FWD, 0);     // 정지
  digitalWrite(DCMOTOR_BWD, 0);
  delay(2000);
  digitalWrite(DCMOTOR_FWD, 0);     // 역방향 회전
  digitalWrite(DCMOTOR_BWD, 1);
  delay(2000);
  digitalWrite(DCMOTOR_FWD, 0);     // 정지
  digitalWrite(DCMOTOR_BWD, 0);
  delay(2000);
}
