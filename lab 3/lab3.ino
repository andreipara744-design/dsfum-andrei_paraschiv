const int pins[] = {8, 9, 10, 11, 12, 13};
const int n = 6;

enum Tip { OFF, FADEIN, FADEOUT, FADEINOUT, BLINK };

struct Led {
  Tip anim;
  unsigned long durata;
  unsigned long start;
  bool activ;
  int lum;
  bool blinkOn;
};

Led led[6];

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < n; i++) {
    pinMode(pins[i], OUTPUT);
    analogWrite(pins[i], 0);
    led[i].anim = OFF;
    led[i].activ = false;
    led[i].lum = 0;
    led[i].blinkOn = false;
  }
  Serial.println("gata. comanda: pin,anim,timp");
}

void loop() {
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();
    proceseaza(cmd);
  }

  unsigned long now = millis();
  for (int i = 0; i < n; i++) {
    if (led[i].activ) update(i, now);
  }
}

void proceseaza(String cmd) {
  int c1 = cmd.indexOf(',');
  int c2 = cmd.indexOf(',', c1 + 1);
  if (c1 == -1 || c2 == -1) {
    Serial.println("format gresit");
    return;
  }

  int pin = cmd.substring(0, c1).toInt();
  String anim = cmd.substring(c1 + 1, c2);
  anim.toLowerCase();
  unsigned long t = cmd.substring(c2 + 1).toInt();

  int idx = -1;
  for (int i = 0; i < n; i++) {
    if (pins[i] == pin) {
      idx = i;
      break;
    }
  }
  if (idx == -1) {
    Serial.println("pin invalid");
    return;
  }

  led[idx].durata = t;
  led[idx].start = millis();
  led[idx].activ = true;
  led[idx].lum = 0;
  led[idx].blinkOn = false;

  if (anim == "off") {
    led[idx].anim = OFF;
    led[idx].activ = false;
    analogWrite(pins[idx], 0);
  }
  else if (anim == "fadein") {
    led[idx].anim = FADEIN;
  }
  else if (anim == "fadeout") {
    led[idx].anim = FADEOUT;
    led[idx].lum = 255;
    analogWrite(pins[idx], 255);
  }
  else if (anim == "fadeinout") {
    led[idx].anim = FADEINOUT;
  }
  else if (anim == "blink") {
    led[idx].anim = BLINK;
  }
  else {
    Serial.println("anim necunoscuta");
    led[idx].activ = false;
  }
}

void update(int i, unsigned long now) {
  unsigned long e = now - led[i].start;
  int p = pins[i];

  if (led[i].anim == FADEIN) {
    if (e >= led[i].durata) {
      analogWrite(p, 255);
      led[i].activ = false;
    } else {
      led[i].lum = map(e, 0, led[i].durata, 0, 255);
      analogWrite(p, led[i].lum);
    }
  }
  else if (led[i].anim == FADEOUT) {
    if (e >= led[i].durata) {
      analogWrite(p, 0);
      led[i].activ = false;
    } else {
      led[i].lum = map(e, 0, led[i].durata, 255, 0);
      analogWrite(p, led[i].lum);
    }
  }
  else if (led[i].anim == FADEINOUT) {
    unsigned long jumatate = led[i].durata / 2;
    if (jumatate == 0) jumatate = 1;
    unsigned long pos = e % led[i].durata;
    if (pos < jumatate) {
      led[i].lum = map(pos, 0, jumatate, 0, 255);
    } else {
      led[i].lum = map(pos - jumatate, 0, jumatate, 255, 0);
    }
    analogWrite(p, led[i].lum);
  }
  else if (led[i].anim == BLINK) {
    unsigned long jumatate = led[i].durata / 2;
    if (jumatate == 0) jumatate = 1;
    bool on = ((e / jumatate) % 2) == 0;
    if (on != led[i].blinkOn) {
      led[i].blinkOn = on;
      analogWrite(p, on ? 255 : 0);
    }
  }
  else {
    analogWrite(p, 0);
    led[i].activ = false;
  }
}