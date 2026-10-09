const int pin = 8;           // pin NON-PWM
int duty = 0;                // 0..255
unsigned long prev = 0;
const unsigned long period = 2000; // 2ms total (aprox 500Hz)

void setup() {
  pinMode(pin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // citire valoare 0..255 de pe serial
  if (Serial.available()) {
    duty = constrain(Serial.parseInt(), 0, 255);
  }

  // software PWM
  unsigned long now = micros();
  unsigned long onTime = (period * duty) / 255;

  if (now - prev >= period) {
    prev = now;
  }

  if (now - prev < onTime) {
    digitalWrite(pin, HIGH);
  } else {
    digitalWrite(pin, LOW);
  }
}