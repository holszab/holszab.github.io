#include <MeMCore.h> // mBot könyvtár

MeUltrasonicSensor ultrasonic(PORT_3); // Távolságérzékelő portja
MeLineFollower colorSensor(PORT_2);   // Színérzékelő portja
MeDCMotor motorLeft(M1);              // Bal motor
MeDCMotor motorRight(M2);             // Jobb motor

void setup() {
  Serial.begin(9600); // Soros monitor az ellenőrzéshez
}

void loop() {
  int distance = ultrasonic.distanceCm(); // Távolság érzékelése
  int lineValue = colorSensor.readSensors(); // Szín érzékelése

  // Piros szín (állj)
  if (lineValue == 1) { // Piros szín esetén (feltételezzük, hogy 1 a piros kódja)
    motorLeft.run(0); // Motorok megállítása
    motorRight.run(0);
    delay(1000); // Várakozás
  }
  // Zöld szín (indulás)
  else if (lineValue == 2) { // Zöld szín esetén (feltételezzük, hogy 2 a zöld kódja)
    motorLeft.run(100); // Motorok indítása
    motorRight.run(100);
  }

  // Gyalogos (akadály) érzékelése
  if (distance < 20) { // Ha akadály van 20 cm-en belül
    motorLeft.run(0); // Motorok megállítása
    motorRight.run(0);
    while (ultrasonic.distanceCm() < 20) {
      delay(100); // Várakozás, amíg a gyalogos el nem távolodik
    }
  }
}
