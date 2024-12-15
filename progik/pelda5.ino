#include <MeMCore.h> // mBot könyvtár

MeLineFollower lineFinder(PORT_2);  // Színérzékelő portja
MeDCMotor motorLeft(M1);            // Bal motor
MeDCMotor motorRight(M2);           // Jobb motor

void setup() {
  Serial.begin(9600); // Soros monitor az ellenőrzéshez
}

void loop() {
  int sensorValue = lineFinder.readSensors(); // Színérzékelő olvasása
  
  switch (sensorValue) {
    case 0x01: // Piros szín kódja
      motorLeft.stop();
      motorRight.stop();
      delay(1000); // Megállás
      break;

    case 0x02: // Zöld szín kódja
      motorLeft.run(50);
      motorRight.run(-50);
      delay(500); // Fordulás jobbra
      break;

    case 0x04: // Kék szín kódja
      motorLeft.run(-50);
      motorRight.run(50);
      delay(500); // Fordulás balra
      break;

    case 0x08: // Sárga szín kódja
      motorLeft.run(100);
      motorRight.run(100);
      delay(1000); // Gyorsítás
      break;

    default: // Alapmozgás (fehér pálya)
      motorLeft.run(70);
      motorRight.run(70);
      break;
  }
  delay(100);
}
