#include <Adafruit_MotorShield.h>
Adafruit_MotorShield AFMS  = Adafruit_MotorShield(); 

constexpr uint8_t ir_port = A1;
constexpr uint8_t ir_stbd = A0;
Adafruit_DCMotor *motor_port = AFMS.getMotor(2);
Adafruit_DCMotor *motor_stbd = AFMS.getMotor(1);

constexpr uint8_t SPEED_STRAIGHT = 25;
constexpr uint8_t SPEED_TURNING  = 25;//100;
constexpr uint8_t SEEING_LINE = 850;

void setup() {
  Serial.begin(9600);

  pinMode(ir_port, INPUT_PULLUP);
  pinMode(ir_stbd, INPUT_PULLUP);

  if(!AFMS.begin()) {
    Serial.println("Motor shield not connected.");
    exit(1);
  }

  motor_port->setSpeed(50);
  motor_stbd->setSpeed(50);
  //motor_port->run(BACKWARD);
  //motor_stbd->run(BACKWARD);
}

// try setting acceleration so that it spins faster the longer it's on the black
// try coming to full stop before turning
// create ir class
// fix the sensors in place
// maybe set an acceleration

void loop() {
  Serial.print(analogRead(ir_port));
  Serial.print(" ");
  Serial.println(analogRead(ir_stbd));

  if(analogRead(ir_port) >= 500) {
    motor_port->run(FORWARD);
    motor_stbd->run(BACKWARD);
  }
  else if(analogRead(ir_stbd) >= 800) {
    motor_port->run(BACKWARD);
    motor_stbd->run(FORWARD);
  }
  else {
    motor_port->run(BACKWARD);
    motor_stbd->run(BACKWARD);
  }
}