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

typedef enum steering_mode_e {
  TANK,
  ARCADE,
} steering_mode_t;

static steering_mode_t steering_mode = TANK;

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
  
  if (controller.xboxNotif.btnDirUp) {
    steering_mode = ARCADE;
  }

  if (controller.xboxNotif.btnDirDown) {
    steering_mode = TANK;
  }

  if (controller.xboxNotif.btnA) {
    weapon_arm();
  }

  if (controller.xboxNotif.btnB) {
    weapon_unarm();
  }

  weapon_set_speed(((float)controller.xboxNotif.trigLT + (float)controller.xboxNotif.trigRT) / (2 * CONTROLLER_TRIGGER_MAX));
  
  float left_ver = -2*(float)controller.xboxNotif.joyLVert / CONTROLLER_JOY_MAX + 1;
  float left_hor = -2*(float)controller.xboxNotif.joyLHori / CONTROLLER_JOY_MAX + 1;
  float right_ver = -2*(float)controller.xboxNotif.joyRVert / CONTROLLER_JOY_MAX + 1;
  
  switch (steering_mode) {
  case TANK:
    motor_set_speed(LEFT, left_ver);
    motor_set_speed(RIGHT, right_ver);
    break;

  case ARCADE:
    // For arcade steering, use right stick vertical for forward/backward
    // and left stick horizontal for turning.
    float left_speed = right_ver - left_hor;  // Adjust left motor speed based on turning
    float right_speed = right_ver + left_hor; // Adjust right motor speed based on turning

    // Ensure speeds stay within the -1 to 1 range
    left_speed = max(-1.0f, min(1.0f, left_speed));
    right_speed = max(-1.0f, min(1.0f, right_speed));

    motor_set_speed(LEFT, left_speed);
    motor_set_speed(RIGHT, right_speed);
    break;
  }
}
