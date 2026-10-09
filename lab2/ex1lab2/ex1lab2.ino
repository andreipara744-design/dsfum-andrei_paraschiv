void setup() {
  for (byte i = 8; i <= 13; i++)
    pinMode(i, OUTPUT);
}

void loop() {
  for (byte n = 0; n <= 63; n++) {
    for (byte i = 0; i < 6; i++) {
      digitalWrite(8 + i, (n >> i) & 1);
    }
    delay(300);//viteza
  }
}