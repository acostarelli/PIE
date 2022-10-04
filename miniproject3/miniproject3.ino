#include <Adafruit_MotorShield.h>
Adafruit_MotorShield AFMS  = Adafruit_MotorShield(); 

constexpr uint8_t ir_port = A1;
constexpr uint8_t ir_stbd = A0;
Adafruit_DCMotor *motor_port = AFMS.getMotor(2);
Adafruit_DCMotor *motor_stbd = AFMS.getMotor(1);

constexpr uint8_t SPEED_STRAIGHT = 25;
constexpr uint8_t SPEED_TURNING  = 50;
constexpr uint8_t SEEING_LINE = 850;

bool seeingline(int ir) {
  return ir >= SEEING_LINE;// && ir <= 950;
}

void setup() {
  Serial.begin(9600);

  pinMode(ir_port, INPUT_PULLUP);
  pinMode(ir_stbd, INPUT_PULLUP);

  if(!AFMS.begin()) {
    Serial.println("Motor shield not connected.");
    exit(1);
  }

  motor_port->run(BACKWARD);
  motor_stbd->run(BACKWARD);
}

void loop() {
  Serial.print(analogRead(ir_port));
  Serial.print(" ");
  Serial.println(analogRead(ir_stbd));
  motor_port->setSpeed(seeingline(analogRead(ir_stbd)) ? SPEED_TURNING : SPEED_STRAIGHT);
  motor_stbd->setSpeed(SPEED_STRAIGHT);
  //motor_stbd->setSpeed(analogRead(ir_port) > SEEING_LINE ? SPEED_TURNING : SPEED_STRAIGHT);
}