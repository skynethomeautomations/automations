#include <Servo.h>
#include <ESP8266WiFi.h>
#include <Homey.h>

// Set WiFi credentials
#define WIFI_SSID "myWifi"
#define WIFI_PASS "myPassword"

Servo myservo1;  // Servo #1
Servo myservo2;  // Servo #2

int offSet = 28;
int offSet2 = 43;
String deviceName = "BedroomBlinds";

void setup() {
  // Setup serial port
  Serial.begin(115200);
  Serial.println();

  // Begin WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  // Connecting to WiFi...
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  // Loop continuously while WiFi is not connected
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }

  // Connected to WiFi
  Serial.println();
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());

  // Attach servo
  myservo1.attach(13);  // attaches the servo on pin 13 to the servo object
  myservo2.attach(14);  // attaches the servo on pin 13 to the servo object

  // Setup Homey
  Homey.begin(deviceName);
  Homey.setClass("windowcoverings");
  Homey.addCapability("dim", setServoPosition);
}

void setServoPosition() {
    // Transfer value get from Homey to a number that servo listens to (between 0 and 180) and add offSet number based on position of servo motor against blinds
    float pos1 = (Homey.value.toFloat() * 70  ) + offSet;
    myservo1.write((int) pos1);
    float pos2 = (Homey.value.toFloat() * 70  ) + offSet2;
    myservo2.write((int) pos2);
}

void loop() {
  Homey.loop();
}
