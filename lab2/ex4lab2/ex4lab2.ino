int led = 9;
int brightness = 0;
int fadeAmount = 5;
unsigned long prev = 0;
unsigned long interval = 30; // viteza implicita

void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // citire viteza de pe serial
  if (Serial.available()) {
    int v = Serial.parseInt();
    if (v > 0) interval = v;
  }

  unsigned long now = millis();
  if (now - prev >= interval) {
    prev = now;
    analogWrite(led, brightness);
    brightness += fadeAmount;

    if (brightness <= 0 || brightness >= 255) {
      fadeAmount = -fadeAmount;
    }
  }
}