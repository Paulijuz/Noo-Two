#include "weapon.hpp"

#include <Arduino.h>

bool armed = false;

void weapon_init() {
  ledcAttachPin(ESC_CONTROL_PIN, ESC_CHANNEL);
  ledcSetup(ESC_CHANNEL, ESC_FREQUENCY, ESC_RESOLUTION);
  ledcWrite(ESC_CHANNEL, ESC_DUTY_MIN);

  for (int i = 0; i < WEAPON_LEDS; i++) {
    ledcAttachPin(weapon_led_pins[i], WEAPON_LEDS_CHANNEL);
  }
  ledcSetup(WEAPON_LEDS_CHANNEL, WEAPON_LEDS_FREQUENCY, ESC_RESOLUTION);
  ledcWrite(WEAPON_LEDS_CHANNEL, 0);

 for (int i = 0; i < WEAPON_LEDS_OFF; i++) {
    ledcAttachPin(weapon_led_off_pins[i], WEAPON_LEDS_OFF_CHANNEL);
  }
  ledcSetup(WEAPON_LEDS_OFF_CHANNEL, WEAPON_LEDS_FREQUENCY, ESC_RESOLUTION);
  ledcWrite(WEAPON_LEDS_OFF_CHANNEL, 0);
}

void weapon_arm() {
  armed = true;
}

void weapon_unarm() {
  armed = false;
  weapon_set_speed(0);
}

void weapon_set_speed(float speed) {
  if (!armed) {
    speed = 0;
  }

  uint32_t duty = ESC_DUTY_MIN + (ESC_DUTY_MAX - ESC_DUTY_MIN) * speed;

  Serial.print(" Weapon Speed: ");
  Serial.print(speed);
  Serial.print(" PWM DUty: ");
  Serial.print(duty);

  ledcWrite(ESC_CHANNEL, duty);
  ledcWrite(WEAPON_LEDS_CHANNEL, 255*speed);
  ledcWrite(WEAPON_LEDS_OFF_CHANNEL, 0);
}
