#pragma once

#define ESC_CHANNEL 0
#define ESC_CONTROL_PIN 22
#define ESC_POWER_PIN 23

#define ESC_DUTY_MIN 12
#define ESC_DUTY_MAX 26

#define WEAPON_LEDS 2

const int weapon_led_pins[] = { 0, 2 };

void weapon_init();
void weapon_set_speed(float speed);