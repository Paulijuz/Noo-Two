#include "weapon.hpp"

#include <Arduino.h>

void weapon_init() {
  ledcAttachPin(ESC_CONTROL_PIN, ESC_CHANNEL);
  ledcSetup(ESC_CHANNEL, ESC_FREQUENCY, 8);
  ledcWrite(ESC_CHANNEL, ESC_DUTY_MIN);

  for (int i = 0; i < WEAPON_LEDS; i++) {
    ledcAttachPin(weapon_led_pins[i], WEAPON_LEDS_CHANNEL);
  }
  ledcSetup(WEAPON_LEDS_CHANNEL, WEAPON_LEDS_FREQUENCY, 8);
  ledcWrite(WEAPON_LEDS_CHANNEL, 0);
}

void weapon_set_speed(float speed) {
  uint32_t duty = ESC_DUTY_MIN + (ESC_DUTY_MAX - ESC_DUTY_MIN) * speed;

  Serial.print(" Weapon Speed: ");
  Serial.print(speed);
  Serial.print(" PWM DUty: ");
  Serial.print(duty);

  ledcWrite(ESC_CHANNEL, duty);
  ledcWrite(WEAPON_LEDS_CHANNEL, 255*speed);
}
