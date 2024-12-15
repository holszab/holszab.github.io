#include <MeMCore.h>

MeColorSensor colorSensor(PORT_3);      // Színérzékelő
MeUltrasonicSensor ultrasonic(PORT_4); // Távolságérzékelő
MeRGBLed rgbLed(PORT_7);               // RGB LED
MeDCMotor motorLeft(M1);
MeDCMotor motorRight(M2);

void setup() {
  Serial.begin(9600);
  rgbLed.setColor(0, 0, 0, 0); // LED alapállapotban kikapcsolva
  rgbLed.show();
}

void loop() {
  int distance = ultrasonic.distanceCm(); // Távolság mérése
  int color = colorSensor.read();         // Színérzékelés

  // Távolság ellenőrzése
  if (distance > 0 && distance < 10) {
    motorLeft.stop();
    motorRight.stop();
    rgbLed.setColor(0, 255, 0, 0); // Piros LED
    rgbLed.show();
    tone(8, 440, 500); // Hangjelzés akadály esetén
    Serial.println("Megállt akadály miatt.");
    delay(500);
    return;
  }

  // Színérzékelés
  switch (color) {
    case 1: // Piros
      motorLeft.stop();
      motorRight.stop();
      rgbLed.setColor(0, 255, 0, 0); // Piros LED
      rgbLed.show();
      tone(8, 440, 500); // Hangjelzés megálláskor
      Serial.println("Piros: Megáll.");
      break;

    case 2: // Sárga
      motorLeft.run(50);
      motorRight.run(50);
      rgbLed.setColor(0, 255, 255, 0); // Sárga LED
      rgbLed.show();
      tone(8, 880, 200); // Rövid hangjelzés lassításkor
      delay(200);
      noTone(8); // Hang kikapcsolása
      Serial.println("Sárga: Lassítás.");
      break;

    case 3: // Zöld
      motorLeft.run(100);
      motorRight.run(100);
      rgbLed.setColor(0, 0, 255, 0); // Zöld LED
      rgbLed.show();
      tone(8, 523, 100); // Rövid hangjelzés haladáskor
      delay(100);
      noTone(8); // Hang kikapcsolása
      Serial.println("Zöld: Haladás.");
      break;

    default:
      motorLeft.stop();
      motorRight.stop();
      rgbLed.setColor(0, 0, 0, 0); // LED kikapcsolása
      rgbLed.show();
      Serial.println("Ismeretlen szín: Megáll.");
  }
  delay(100);
}