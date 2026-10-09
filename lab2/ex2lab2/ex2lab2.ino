void setup() {
  Serial.begin(9600);
  for (byte i = 8; i <= 13; i++)
    pinMode(i, OUTPUT);
}

void loop() {
  if (Serial.available()) {
    int n = Serial.parseInt();
    n = constrain(n, 0, 63);

    for (byte i = 0; i < 6; i++) {
      digitalWrite(8 + i, (n >> i) & 1);
    }
  }
}