#include <MeMCore.h> // mBot könyvtár

MeUltrasonicSensor ultrasonic(PORT_3); // Távolságérzékelő portja
MeLineFollower colorSensor(PORT_2);   // Színérzékelő portja
MeDCMotor motorLeft(M1);              // Bal motor
MeDCMotor motorRight(M2);             // Jobb motor

void setup() {
  Serial.begin(9600); // Soros monitor az ellenőrzéshez
}

void loop() {
  // Távolság érzékelése
  int distance = ultrasonic.distanceCm();
  
  if (distance < 20) { // Ha akadály 20 cm-en belül
    motorLeft.run(-50);
    motorRight.run(50);
    delay(500); // Forduljon jobbra
  } else {
    // Színérzékelés
    int colorValue = colorSensor.readSensors();
    
    switch (colorValue) {
      case 0x01: // Piros szín
        motorLeft.stop();
        motorRight.stop();
        delay(1000); // Megállás
        break;

      case 0x02: // Zöld szín
        motorLeft.run(100);
        motorRight.run(100);
        delay(500); // Gyorsítás
        break;

      case 0x04: // Kék szín
        motorLeft.run(-50);
        motorRight.run(50);
        delay(500); // Balra fordulás
        break;

      default: // Alapmozgás (fehér pálya)
        motorLeft.run(70);
        motorRight.run(70);
        break;
    }
  }

  delay(100);
}
