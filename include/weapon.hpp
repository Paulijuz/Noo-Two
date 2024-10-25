#pragma once

#define ESC_CHANNEL 0
#define ESC_CONTROL_PIN 22
#define ESC_POWER_PIN 23

#define ESC_DUTY_MIN 12
#define ESC_DUTY_MAX 26
#define ESC_FREQUENCY 2000

#define WEAPON_LEDS 2
#define WEAPON_LEDS_CHANNEL 1
#define WEAPON_LEDS_FREQUENCY ESC_FREQUENCY

const int weapon_led_pins[] = { 0, 2 };

void weapon_init();
void weapon_set_speed(float speed);