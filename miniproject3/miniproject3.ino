#include <Adafruit_MotorShield.h>

class ROS {
  public:
    ROS(uint8_t *pin, int threshold) {
      _pin = pin;
      _threshold = threshold;
    }

    bool seeing_line() {
      return analogRead(_pin) >= _threshold;
    }

    void debug() {
      Serial.print(analogRead(_pin));
    }
  
  private:
    uint8_t *_pin;
    int _threshold;
};
ROS ir_port = ROS(A1, 500);
ROS ir_stbd = ROS(A0, 800);

Adafruit_MotorShield AFMS  = Adafruit_MotorShield(); 
Adafruit_DCMotor *motor_port = AFMS.getMotor(2);
Adafruit_DCMotor *motor_stbd = AFMS.getMotor(1);

constexpr uint8_t SPEED = 25;

void setup() {
  Serial.begin(9600);

  if(!AFMS.begin()) {
    Serial.println("Motor shield not connected.");
    exit(1);
  }

  motor_port->setSpeed(SPEED);
  motor_stbd->setSpeed(SPEED);
}

void loop() {
  motor_port->run(ir_port.seeing_line() ? FORWARD : BACKWARD);
  motor_stbd->run(ir_stbd.seeing_line() ? FORWARD : BACKWARD);
}