const int pin = 8;
int brightness = 0;
int fadeAmount = 5;
unsigned long prevFade = 0;
unsigned long fadeInterval = 30;

unsigned long prevPwm = 0;
const unsigned long period = 2000; // 2ms

void setup() {
  pinMode(pin, OUTPUT);
}

void loop() {
  // actualizare brightness
  unsigned long now = millis();
  if (now - prevFade >= fadeInterval) {
    prevFade = now;
    brightness += fadeAmount;
    if (brightness <= 0 || brightness >= 255) {
      fadeAmount = -fadeAmount;
    }
  }

  // software PWM
  unsigned long t = micros();
  unsigned long onTime = (period * brightness) / 255;

  if (t - prevPwm >= period) {
    prevPwm = t;
  }

  digitalWrite(pin, (t - prevPwm < onTime) ? HIGH : LOW);
}