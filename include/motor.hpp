#pragma once

// Left motor
#define MOTOR_LEFT_SPEED_PIN 14
#define MOTOR_LEFT_FORWARDS_PIN 26
#define MOTOR_LEFT_BACKWARDS_PIN 27

// Right motor
#define MOTOR_RIGHT_FORWARDS_PIN 33
#define MOTOR_RIGHT_BACKWARDS_PIN 25
#define MOTOR_RIGHT_SPEED_PIN 32

// Both motors
#define MOTOR_DEADZONE 0.25

typedef enum motor_side_e {
  LEFT,
  RIGHT,
} motor_side_t;

void motor_init();
void motor_set_speed(motor_side_t side, float speed);