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
constexpr Servo servo_pan;
constexpr Servo servo_tilt;

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
  servo_pan .attach(pin_pan , PWM_MIN, PWM_MAX);
  servo_tilt.attach(pin_tilt, PWM_MIN, PWM_MAX);

  Serial.begin(BAUD);
}

void loop() {
  angle_pan  = 0;
  angle_tilt = 0;
  
  servo_pan .write(0);

  for(int angle_pan = 0; angle_pan < 181; angle_pan++) {
    servo_pan.write(angle_pan);

    for(int angle_tilt = 0; angle_tilt < 181; angle_tilt++) {
      servo_tilt.write(angle_tilt);
      delay(DELAY);
      write(angle_pan, angle_tilt * 2, analogRead(pin_ir));
    }
  }

  end();
}