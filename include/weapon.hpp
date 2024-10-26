#pragma once

#define ESC_CHANNEL 0
#define ESC_RESOLUTION 8
#define ESC_CONTROL_PIN 22
#define ESC_POWER_PIN 23

#define ESC_DUTY_MIN 12
#define ESC_DUTY_MAX 26
#define ESC_FREQUENCY 50

#define WEAPON_LEDS 3
#define WEAPON_LEDS_CHANNEL 1
#define WEAPON_LEDS_FREQUENCY ESC_FREQUENCY

const int weapon_led_pins[WEAPON_LEDS] = { 2, 17, 19 };

void weapon_init();
void weapon_arm();
void weapon_unarm();
void weapon_set_speed(float speed);