#include <MeMCore.h> // mBot könyvtár

MeLineFollower lineSensor(PORT_2);      // Vonalkövető érzékelő
MeRGBLed rgbLed(PORT_7);                // RGB LED az állomások jelzésére
MeColorSensor colorSensor(PORT_3);      // Színérzékelő
MeUltrasonicSensor ultrasonic(PORT_4);  // Távolságérzékelő
MeDCMotor motorLeft(M1);                // Bal motor
MeDCMotor motorRight(M2);               // Jobb motor

void setup() {
  Serial.begin(9600); // Soros monitor indítása
  rgbLed.setColor(0, 0, 0, 0); // LED alapállapot: kikapcsolva
  rgbLed.show();
}

void loop() {
  int lineStatus = lineSensor.readSensors(); // Vonalkövető érzékelése
  String detectedColor = colorSensor.returnColorName(); // Színérzékelés
  int distance = ultrasonic.distanceCm(); // Távolság mérése

  int speed = adjustSpeed(distance); // Sebesség kiszámítása a távolság alapján

  // Vonalkövetés sebességszabályozással
  if (lineStatus == 2) { // Mindkét szenzor a vonalon
    motorLeft.run(speed);
    motorRight.run(speed);
  } else if (lineStatus == 1) { // Jobb szenzor a vonalon
    motorLeft.run(speed);
    motorRight.run(speed / 2);
  } else if (lineStatus == 3) { // Bal szenzor a vonalon
    motorLeft.run(speed / 2);
    motorRight.run(speed);
  }

  // Színérzékelés és speciális műveletek
  if (detectedColor == "red") { // Piros állomás
    Serial.println("Piros állomás: Megállás és várakozás.");
    stopAndWait();
  } else if (detectedColor == "green") { // Zöld állomás
    Serial.println("Zöld állomás: Továbbhaladás.");
    motorLeft.run(speed);
    motorRight.run(speed);
  } else if (detectedColor == "blue") { // Kék állomás
    Serial.println("Kék állomás: Speciális művelet (villogás).");
    blinkLed(0, 0, 255, 5); // Kék LED villogás
  }
}

// Sebesség szabályozása a távolság alapján
int adjustSpeed(int distance) {
  if (distance > 0 && distance <= 10) {
    return 50; // Lassú haladás (közel az állomáshoz)
  } else if (distance > 10 && distance <= 30) {
    return 80; // Közepes sebesség
  } else {
    return 100; // Normál sebesség
  }
}

// Robot megállása és várakozása
void stopAndWait() {
  motorLeft.run(0);
  motorRight.run(0);
  delay(5000); // 5 másodperces várakozás
}

// LED villogtatása
void blinkLed(int red, int green, int blue, int times) {
  for (int i = 0; i < times; i++) {
    rgbLed.setColor(0, red, green, blue); // LED bekapcsolás
    rgbLed.show();
    delay(500);
    rgbLed.setColor(0, 0, 0, 0); // LED kikapcsolás
    rgbLed.show();
    delay(500);
  }
}
