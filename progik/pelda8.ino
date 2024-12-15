#include <MeMCore.h>

MeUltrasonicSensor ultrasonic(PORT_3); // Távolságérzékelő
MeDCMotor motorLeft(M1);               // Bal motor
MeDCMotor motorRight(M2);              // Jobb motor

void setup() {
  Serial.begin(9600);
}

void loop() {
  int distance = ultrasonic.distanceCm(); // Távolság mérése

  if (distance > 50) { // Ha a másik robot távol van
    motorLeft.run(100);
    motorRight.run(100); // Gyorsítás előre
  } else if (distance < 30) { // Ha a másik robot közel van
    motorLeft.run(-100);
    motorRight.run(-100); // Hátrafelé húzás
  } else {
    motorLeft.run(50);
    motorRight.run(50); // Lassú haladás
  }

  delay(100);
}
