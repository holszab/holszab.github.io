#include <MeMCore.h>

MeUltrasonicSensor ultrasonic(PORT_3);
MeLineFollower colorSensor(PORT_2);
MeDCMotor motorLeft(M1);
MeDCMotor motorRight(M2);

int speedFast = 150;
int speedSlow = 50;
int speedStop = 0;
int speedDefault = 100;

int colorGreen = 1;
int colorYellow = 2;
int colorRed = 3;

int obstacleThreshold = 15;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int distance = ultrasonic.distanceCm();
  int color = colorSensor.readSensors();

  if (distance < obstacleThreshold) {
    motorLeft.run(-100);
    motorRight.run(-100);
    delay(500);

    motorLeft.run(100);
    motorRight.run(-100);
    delay(300);
  } else {
    if (color == colorGreen) {
      motorLeft.run(speedFast);
      motorRight.run(speedFast);
    } else if (color == colorYellow) {
      motorLeft.run(speedSlow);
      motorRight.run(speedSlow);
    } else if (color == colorRed) {
      motorLeft.run(speedStop);
      motorRight.run(speedStop);
      delay(1000);
    } else {
      motorLeft.run(speedDefault);
      motorRight.run(speedDefault);
    }
  }

  delay(100);
}
