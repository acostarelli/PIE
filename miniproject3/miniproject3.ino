#include <Adafruit_MotorShield.h>
Adafruit_MotorShield AFMS  = Adafruit_MotorShield(); 

constexpr uint8_t ir_port  = 9;
constexpr uint8_t ir_stbd = 10;
Adafruit_DCMotor *motor_port = AFMS.getMotor(1);
Adafruit_DCMotor *motor_stbd = AFMS.getMotor(2);

constexpr uint8_t SPEED_STRAIGHT = 127;
constexpr uint8_t SPEED_TURNING  = 200;
constexpr uint8_t SEEING_BLACK = LOW;

void setup() {
  Serial.begin(9600);

  pinMode(ir_port, INPUT_PULLUP);
  pinMode(ir_stbd, INPUT_PULLUP);

  if(!AFMS.begin()) {
    Serial.println("Motor shield not connected.");
    exit(1);
  }

  motor_port->run(FORWARD);
  motor_stbd->run(FORWARD);
}

void loop() {
  motor_port->setSpeed(digitalRead(ir_port) == SEEING_BLACK ? SPEED_TURNING : SPEED_STRAIGHT);
  motor_stbd->setSpeed(digitalRead(ir_stbd) == SEEING_BLACK ? SPEED_TURNING : SPEED_STRAIGHT);
}