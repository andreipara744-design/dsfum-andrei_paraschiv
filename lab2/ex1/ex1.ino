const int ledPin = 13;
unsigned long previousMillis = 0;
const unsigned long interval = 5000; // 5s
bool ledState = LOW;
bool blinkMode = false;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("1=pornit 2=oprit 3=blink");
}

void loop() {
  // citire serial
  if (Serial.available() > 0) {
    char opt = Serial.read();
    if (opt == '\n' || opt == '\r') return;

    switch (opt) {
      case '1':
        Serial.println("pornit");
        blinkMode = false;
        digitalWrite(ledPin, HIGH);
        break;

      case '2':
        Serial.println("oprit");
        blinkMode = false;
        digitalWrite(ledPin, LOW);
        break;

      case '3':
        Serial.println("blink");
        blinkMode = true;
        previousMillis = millis();
        break;

      default:
        Serial.println("invalid");
        break;
    }
  }

  // blink non-blocant
  if (blinkMode) {
    unsigned long now = millis();
    if (now - previousMillis >= interval) {
      previousMillis = now;
      ledState = !ledState;
      digitalWrite(ledPin, ledState);
    }
  }
}