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
  int lineValue = colorSensor.readSensors(); // Fekete vonal érzékelése
  
  // Ha a robot a pálya határára ér (fekete vonal)
  if (lineValue == 3) { 
    motorLeft.run(-50);
    motorRight.run(-50);
    delay(500); // Visszatolatás
    motorLeft.run(50);
    motorRight.run(-50);
    delay(500); // Kanyarodás
  } 
  else if (distance < 20) { // Ha a labda 20 cm-en belül van
    motorLeft.run(100);
    motorRight.run(100); // Követi a labdát
  } 
  else if (distance < 50) { // Ha a labda kicsit távolabb van
    motorLeft.run(70);
    motorRight.run(70); // Lassabban halad a labda felé
  } 
  else { // Ha sem labda, sem fekete vonal nincs közel
    motorLeft.run(50);
    motorRight.run(50); // Egyenes haladás
  }

  delay(100); // Kis szünet az érzékelők frissítéséhez
}
