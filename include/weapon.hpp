#pragma once

#define ESC_CHANNEL 0
#define ESC_RESOLUTION 8
#define ESC_CONTROL_PIN 22
#define ESC_POWER_PIN 23

#define ESC_DUTY_MIN 12
#define ESC_DUTY_MAX 26
#define ESC_FREQUENCY 50

#define WEAPON_LEDS 3
#define WEAPON_LEDS_OFF 4
#define WEAPON_LEDS_CHANNEL 5
#define WEAPON_LEDS_OFF_CHANNEL 1
#define WEAPON_LEDS_FREQUENCY 50

const int weapon_led_pins[WEAPON_LEDS] = { 
    21, // R
    17, // R
    2, // Internal
};

const bool weapon_led_off_pins[WEAPON_LEDS_OFF] = { 
    19, // B
    18, // G
    16, // B
    4, // G
};

void weapon_init();
void weapon_arm();
void weapon_unarm();
void weapon_set_speed(float speed);