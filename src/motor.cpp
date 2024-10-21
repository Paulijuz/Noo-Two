#include "motor.hpp"

#include <Arduino.h>

void motor_init() {
  pinMode(MOTOR_LEFT_FORWARDS_PIN, OUTPUT);
  pinMode(MOTOR_LEFT_BACKWARDS_PIN, OUTPUT);
  pinMode(MOTOR_RIGHT_FORWARDS_PIN, OUTPUT);
  pinMode(MOTOR_RIGHT_BACKWARDS_PIN, OUTPUT);
}

void motor_set_speed(motor_side_t side, float speed) {
  int forwards_pin, backwards_pin, speed_pin;
  const char* side_name;

  // TODO: Refactor
  if (side == LEFT) {
    forwards_pin = MOTOR_LEFT_FORWARDS_PIN;
    backwards_pin = MOTOR_LEFT_BACKWARDS_PIN;
    speed_pin = MOTOR_LEFT_SPEED_PIN;
    side_name = "Left";
  } else {  // RIGHT
    forwards_pin = MOTOR_RIGHT_FORWARDS_PIN;
    backwards_pin = MOTOR_RIGHT_BACKWARDS_PIN;
    speed_pin = MOTOR_RIGHT_SPEED_PIN;
    side_name = "Right";
  }

  Serial.print(" ");
  Serial.print(side_name);
  Serial.print(" Speed: ");
  Serial.print(speed);
  Serial.print(" Direction: ");
  
  // Deadzone
  if (abs(speed) < MOTOR_DEADZONE) {
    Serial.print("Nope");
    digitalWrite(forwards_pin, LOW);
    digitalWrite(backwards_pin, LOW);
    return;
  }

  // Set motor direction
  if (speed > 0) {
    Serial.print("Forwards");
    digitalWrite(forwards_pin, HIGH);
    digitalWrite(backwards_pin, LOW);
  } else {
    Serial.print("Backwards");
    digitalWrite(forwards_pin, LOW);
    digitalWrite(backwards_pin, HIGH);
  }

  // Set motor speed
  analogWrite(speed_pin, 255 * abs(speed));
}

