#include <RPLidar.h>
#include <Servo.h>

#define RPLIDAR_MOTOR_PIN 3
#define FIRST_SCAN_SECONDS 30
#define SECOND_SCAN_SECONDS 30
#define DELAY_SECONDS 20
#define SERVO_PIN 4
#define ANGLE 45

Servo servo;
RPLidar lidar;

void setup() {
  lidar.begin(Serial1);
  Serial.begin(115200);

  pinMode(RPLIDAR_MOTOR_PIN, OUTPUT);

  if (!lidar.begin(Serial1)) {
    Serial.println("Communication with RPLidar failed!");
    while (1); // Stop the loop if communication failed
  }
}

void loop() {
  unsigned long scanStartTime = millis();
  while ((millis() - scanStartTime) < (FIRST_SCAN_SECONDS * 1000)) {
    if(IS_OK(lidar.waitPoint())) {
      float distance = lidar.getCurrentPoint().distance;
      float angle = lidar.getCurrentPoint().angle;
      byte quality = lidar.getCurrentPoint().quality;

      unsigned long currentTime = millis() - scanStartTime;
    
      Serial.print(angle);
      Serial.print("; ");
      Serial.print(distance);
      Serial.print("; ");
      Serial.println(quality);
    } else {
      analogWrite(RPLIDAR_MOTOR_PIN, 0);

      rplidar_response_device_info_t info;
      if(IS_OK(lidar.getDeviceInfo(info, 100))) {
        lidar.startScan();
        analogWrite(RPLIDAR_MOTOR_PIN, 255);
        delay(1000);
      }
    }
  } 

  analogWrite(RPLIDAR_MOTOR_PIN, 0);
  Serial.println("First scan completed.");

  delay(DELAY_SECONDS * 1000);

  servo.attach(SERVO_PIN);
  servo.write(ANGLE);
  delay(1000);

  scanStartTime = millis();
  while ((millis() - scanStartTime) < (SECOND_SCAN_SECONDS * 1000)) {
    if(IS_OK(lidar.waitPoint())) {
      float distance = lidar.getCurrentPoint().distance;
      float angle = lidar.getCurrentPoint().angle;
      byte quality = lidar.getCurrentPoint().quality;

      unsigned long currentTime = millis() - scanStartTime;
    
      Serial.print(angle);
      Serial.print("; ");
      Serial.print(distance);
      Serial.print("; ");
      Serial.println(quality);
    } else {
      analogWrite(RPLIDAR_MOTOR_PIN, 0);

      rplidar_response_device_info_t info;
      if(IS_OK(lidar.getDeviceInfo(info, 100))) {
        lidar.startScan();
        analogWrite(RPLIDAR_MOTOR_PIN, 255);
        delay(1000);
      }
    }
  } 

  analogWrite(RPLIDAR_MOTOR_PIN, 0);
  Serial.println("Second scan completed.");
  servo.write(0);
  delay(1000);
  servo.detach();
  while (1); // Stop the loop after the scan is completed
}

