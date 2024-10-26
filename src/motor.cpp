#include "motor.hpp"

#include <Arduino.h>

void motor_init() {
  pinMode(MOTOR_LEFT_FORWARDS_PIN, OUTPUT);
  pinMode(MOTOR_LEFT_BACKWARDS_PIN, OUTPUT);

  ledcAttachPin(MOTOR_LEFT_SPEED_PIN, MOTOR_LEFT_PWM_CHANNEL);
  ledcSetup(MOTOR_LEFT_PWM_CHANNEL, MOTOR_PWM_FREQUENCY, MOTOR_PWM_RESOLUTION);
  ledcWrite(MOTOR_LEFT_PWM_CHANNEL, 0);

  pinMode(MOTOR_RIGHT_FORWARDS_PIN, OUTPUT);
  pinMode(MOTOR_RIGHT_BACKWARDS_PIN, OUTPUT);

  ledcAttachPin(MOTOR_RIGHT_SPEED_PIN, MOTOR_RIGHT_PWM_CHANNEL);
  ledcSetup(MOTOR_RIGHT_PWM_CHANNEL, MOTOR_PWM_FREQUENCY, MOTOR_PWM_RESOLUTION);
  ledcWrite(MOTOR_RIGHT_PWM_CHANNEL, 0);
}

void motor_set_speed(motor_side_t side, float speed) {
  int forwards_pin, backwards_pin, pwm_channel;
  const char* side_name;

  // TODO: Refactor
  if (side == LEFT) {
    forwards_pin = MOTOR_LEFT_FORWARDS_PIN;
    backwards_pin = MOTOR_LEFT_BACKWARDS_PIN;
    side_name = "Left";
    pwm_channel = MOTOR_LEFT_PWM_CHANNEL;
  } else {  // RIGHT
    forwards_pin = MOTOR_RIGHT_FORWARDS_PIN;
    backwards_pin = MOTOR_RIGHT_BACKWARDS_PIN;
    side_name = "Right";
    pwm_channel = MOTOR_RIGHT_PWM_CHANNEL;
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
  ledcWrite(pwm_channel, 255 * abs(speed));
}

