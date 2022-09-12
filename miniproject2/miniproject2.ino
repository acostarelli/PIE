#include <Servo.h>

/** Sketch parameters
 * Pins for the servos must be PWM.
 */
constexpr int pin_pan  = 9;
constexpr int pin_tilt = 10;
constexpr int pin_ir   = A0;

/** Constants */
constexpr int PWM_MIN = 800;
constexpr int PWM_MAX = 2200;
constexpr int BAUD    = 115200;
constexpr int DELAY   = 15;

/** Globals */
Servo servo_pan;
Servo servo_tilt;

void send(int angle_pan, int angle_tilt, float radius) {
  Serial.print(angle_pan);
  Serial.print(' ');
  Serial.print(angle_tilt);
  Serial.print(' ');
  Serial.print(radius);
  Serial.print('\n');
}

/** Tell Python data collection is over, and halt the Arduino. */
void end() {
  Serial.println("end");
  while(true) {delay(1000);}
}

void setup() {
  Serial.begin(BAUD);

  servo_pan .attach(pin_pan , PWM_MIN, PWM_MAX);
  servo_tilt.attach(pin_tilt, PWM_MIN, PWM_MAX);

  servo_pan .write(0);
  servo_tilt.write(0);
  delay(2000);
}

/** Scan a 3D object
 * Loop pan angle from 0 to 180, loop tilt angle from 0 to 180 then 180 to 0
 * for each pan angle. Send the data to Python after each movement.
 */
void loop() {
  for(int angle_pan = 0; angle_pan <= 180; angle_pan+=2) {
    int angle_tilt = 0;

    servo_pan.write(angle_pan);
    for(; angle_tilt <= 180; angle_tilt++) {
      servo_tilt.write(angle_tilt);
      delay(DELAY);
      send(angle_pan * 2, angle_tilt, analogRead(pin_ir));
    }

    servo_pan.write(angle_pan+1);
    for(; angle_tilt >= 0; angle_tilt--) {
      servo_tilt.write(angle_tilt);
      delay(DELAY);
      send((angle_pan+1) * 2, angle_tilt, analogRead(pin_ir));
    }
  }

  end();
}