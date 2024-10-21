#include "motor.hpp"
#include "weapon.hpp"

#include <Arduino.h>
#include <XboxSeriesXControllerESP32_asukiaaa.hpp>

// Xbox controller
#define CONTROLLER_ADDRESS "44:16:22:9c:5a:4f"
#define CONTROLLER_JOY_MAX XboxControllerNotificationParser::maxJoy
#define CONTROLLER_TRIGGER_MAX XboxControllerNotificationParser::maxTrig

XboxSeriesXControllerESP32_asukiaaa::Core controller(CONTROLLER_ADDRESS);

unsigned long last_notification_received_at = 0;

void setup() {
  Serial.begin(115200);

  pinMode(ESC_POWER_PIN, OUTPUT);
  digitalWrite(ESC_POWER_PIN, HIGH);

  motor_init();
  weapon_init();

  Serial.print("\nSearching for controller...");
  controller.begin();
}

void loop() {
  delay(50);

  Serial.print("\33[2K\r");
  controller.onLoop();

  if (!controller.isConnected()) {
    Serial.print("Connection lost.");
    
    weapon_set_speed(0);
    motor_set_speed(LEFT, 0);
    motor_set_speed(RIGHT, 0);

    if (controller.getCountFailedConnection() > 2) {
      Serial.print(" Restarting ESP due to lost connection!");
      ESP.restart();
    }

    Serial.print(" Trying to reconnect...");
    return;
  }

  if (controller.isWaitingForFirstNotification()) {
    Serial.print("Paired! Waiting for first notification...");
    
    weapon_set_speed(0);
    motor_set_speed(LEFT, 0);
    motor_set_speed(RIGHT, 0);
    
    return;
  }

  last_notification_received_at = controller.getReceiveNotificationAt();

  Serial.print("Time: ");
  Serial.print(last_notification_received_at);

  Serial.print(" Recieved at: ");
  Serial.print(last_notification_received_at);

  weapon_set_speed((float)controller.xboxNotif.trigRT / CONTROLLER_TRIGGER_MAX);
  
  motor_set_speed(LEFT, -2*(float)controller.xboxNotif.joyLVert / CONTROLLER_JOY_MAX + 1);
  motor_set_speed(RIGHT, -2*(float)controller.xboxNotif.joyRVert / CONTROLLER_JOY_MAX + 1);
}