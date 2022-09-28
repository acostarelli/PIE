/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 https://www.arduino.cc/en/Tutorial/LibraryExamples/Sweep
*/

#include <Servo.h>

Servo base_servo;  // create servo object to control a servo
Servo sensor_servo;

int pos = 50;    // variable to store the servo position
int angle = 0;  // bottom starting angle
const int sensorPin = A0;
int sensorValue = 0;

void setup() {
  Serial.flush();
  base_servo.attach(9);  // attaches the servo on pin 9 to the servo object
  sensor_servo.attach(10);
  Serial.begin(9600);
}

// 105 degrees is "center" for sensor value
// 100 degrees is "center" for base value
// return pan, tilt, voltage
void loop() {
  sensor_servo.write(105);  // 105- 60
  base_servo.write(50);

  // from side to side
  for (pos = 50; pos <= 120; pos += 5) {  // 100 degrees is the
    base_servo.write(pos);               // tell servo to go to position in variable 'pos'
    // tilt sensor to scan entire length
    for (angle = 165; angle >= 75; angle -= 1) {
      sensor_servo.write(angle);
      sensorValue = analogRead(sensorPin);
      Serial.print(pos);
      Serial.flush();
      Serial.print(" ");
      Serial.flush();
      Serial.print(angle);
      Serial.flush();
      Serial.print(" ");
      Serial.flush();
      Serial.println(sensorValue);
      Serial.flush();
      delay(15);
    }
    delay(30);  // waits 15 ms for the servo to reach the position
    if (pos == 120) {
      exit(0);
    }
  }
}