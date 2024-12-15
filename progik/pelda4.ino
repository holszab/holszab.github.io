#include <MeMCore.h> // mBot könyvtár

MeUltrasonicSensor ultrasonic(PORT_3); // Távolságérzékelő portja
MeLineFollower colorSensor(PORT_2);   // Színérzékelő portja
MeBuzzer buzzer;                      // Hangjelző
MeDCMotor motorLeft(M1);              // Bal motor
MeDCMotor motorRight(M2);             // Jobb motor

void keresUzemmod() {
  int distance = ultrasonic.distanceCm();

  if (distance < 15) { // Ha akadály van 15 cm-en belül
    motorLeft.run(-100); // Hátramenet
    motorRight.run(-100);
    delay(500);

    motorLeft.run(100); // Fordulás jobbra
    motorRight.run(-100);
    delay(300);
  } else {
    motorLeft.run(100); // Haladás előre
    motorRight.run(100);
  }
}

void mentesFelismeres() {
  int lineValue = colorSensor.readSensors();

  if (lineValue == 1) { // Piros szín észlelése (pl. piros kód = 1)
    motorLeft.run(0); // Robot megáll
    motorRight.run(0);
    buzzer.tone(500, 1000); // Hangjelzés
    delay(2000);            // Két másodperc jelzés
    visszateres();
  }
}

void visszateres() {
  motorLeft.run(-100); // Robot hátrafelé halad
  motorRight.run(-100);
  delay(2000); // Egy egyszerű visszatérési mozgás
}

void setup() {
  Serial.begin(9600); // Soros monitor az ellenőrzéshez
}

void loop() {
  keresUzemmod();
  mentesFelismeres();
}
