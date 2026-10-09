const byte pins[] = {8, 9, 10, 11, 12, 13};
int brightness[6] = {0};
int fadeAmount[6] = {3, 5, 7, 4, 6, 8}; // viteze diferite
unsigned long prev[6] = {0};
unsigned long interval[6] = {20, 30, 25, 35, 15, 40};

void setup() {
  for (byte i = 0; i < 6; i++)
    pinMode(pins[i], OUTPUT);
}

void loop() {
  unsigned long now = millis();

  for (byte i = 0; i < 6; i++) {
    if (now - prev[i] >= interval[i]) {
      prev[i] = now;
      brightness[i] += fadeAmount[i];

      if (brightness[i] <= 0 || brightness[i] >= 255) {
        fadeAmount[i] = -fadeAmount[i];
      }

      // pe pinii PWM folosim analogWrite, pe restul digitalWrite simplu
      if (pins[i] == 9 || pins[i] == 10 || pins[i] == 11) {
        analogWrite(pins[i], brightness[i]);
      } else {
        digitalWrite(pins[i], brightness[i] > 127);
      }
    }
  }
}