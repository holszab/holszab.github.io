#include <MeMCore.h> // mBot könyvtár

MeUltrasonicSensor ultrasonic(PORT_3); // Távolságérzékelő
MeLineFollower colorSensor(PORT_2);   // Színérzékelő
MeDCMotor motorLeft(M1);              // Bal motor
MeDCMotor motorRight(M2);             // Jobb motor

void setup() {
  Serial.begin(9600); // Soros monitor az ellenőrzéshez
}

void loop() {
  int distance = ultrasonic.distanceCm(); // Távolság mérése
  int color = colorSensor.readSensors();  // Szín olvasása

  // Színkódok: 1 = zöld (szabad), 2 = kék (rokkant), 3 = sárga (családi)
  if (color == 1) { // Szabad hely (zöld)
    Serial.println("Szabad parkolóhely: zöld!");
    parkol();
  } else if (color == 2) { // Rokkant parkolóhely (kék)
    if (userPrefersDisabled()) {
      Serial.println("Rokkant parkolóhely választva!");
      parkol();
    } else {
      Serial.println("Rokkant parkolóhely, továbbhaladás...");
      keresTovabb();
    }
  } else if (color == 3) { // Családi parkolóhely (sárga)
    if (userPrefersFamily()) {
      Serial.println("Családi parkolóhely választva!");
      parkol();
    } else {
      Serial.println("Családi parkolóhely, továbbhaladás...");
      keresTovabb();
    }
  } else {
    // Ha nincs érvényes színkód, haladjon tovább
    keresTovabb();
  }

  delay(100); // Rövid szünet az érzékelők számára
}

// Funkció a parkoláshoz
void parkol() {
  motorLeft.run(0);       // Megállás
  motorRight.run(0);
  delay(500);

  // Pozicionálás a parkolóhely közepére
  while (ultrasonic.distanceCm() > 5) {
    motorLeft.run(50);
    motorRight.run(50);
  }

  // Parkolási manőver
  motorLeft.run(-50); // Hátramenet a pontos parkolásért
  motorRight.run(-50);
  delay(500);

  motorLeft.run(0); // Végső megállás
  motorRight.run(0);
  Serial.println("Parkolás kész!");
  delay(5000); // Parkolás befejezése
}

// Funkció a további kereséshez
void keresTovabb() {
  motorLeft.run(100);
  motorRight.run(100);
}

// Felhasználói preferenciák
bool userPrefersDisabled() {
  // Állítsd be, hogy a felhasználó előnyben részesíti-e a rokkant parkolót
  return false; // Módosítsd igény szerint
}

bool userPrefersFamily() {
  // Állítsd be, hogy a felhasználó előnyben részesíti-e a családi parkolót
  return true; // Módosítsd igény szerint
}
