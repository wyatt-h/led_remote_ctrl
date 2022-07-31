#include <WiFiClientSecure.h>
#include <MQTTClient.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <string>

#include "secrets.hpp"
#include "led_strip.hpp"

using namespace std;

// The MQTT topics that this device should publish/subscribe
#define AWS_IOT_PUBLISH_TOPIC   "esp32/pub"
#define AWS_IOT_SUBSCRIBE_TOPIC "led_ctrl"
#define LED_COUNT 60
#define PIN 16

WiFiClientSecure net = WiFiClientSecure();
MQTTClient client = MQTTClient(256);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, PIN, NEO_GRB + NEO_KHZ800);
LedStrip ledstrip;
string mode = "";

void publishMessage()
{
  StaticJsonDocument<200> doc;
  doc["time"] = millis();
  doc["sensor_a0"] = analogRead(0);
  char jsonBuffer[512];
  serializeJson(doc, jsonBuffer); // print to client

  client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer);
}

void messageHandler(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);

  StaticJsonDocument<200> doc;
  deserializeJson(doc, payload);
  const char* message = doc["mode"];
  ledstrip.setMode(message);
  Serial.println(message);
}


void connectAWS()
{
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Configure WiFiClientSecure to use the AWS IoT device credentials
  net.setCACert(AWS_CERT_CA);
  net.setCertificate(AWS_CERT_CRT);
  net.setPrivateKey(AWS_CERT_PRIVATE);

  // Connect to the MQTT broker on the AWS endpoint we defined earlier
  client.begin(AWS_IOT_ENDPOINT, 8883, net);

  // Create a message handler
  client.onMessage(messageHandler);

  Serial.print("Connecting to AWS IOT");

  while (!client.connect(THINGNAME)) {
    Serial.print(".");
    delay(100);
  }
  Serial.println();

  if(!client.connected()){
    Serial.println("AWS IoT Timeout!");
    return;
  }

  // Subscribe to a topic
  client.subscribe(AWS_IOT_SUBSCRIBE_TOPIC);

  Serial.println("AWS IoT Connected!");
}


void setup() {
  Serial.begin(9600);
  // ledstrip.init(LED_COUNT, PIN);
  ledstrip.init(strip);
  delay(100);
  connectAWS();
}

void loop() {
  // publishMessage();
  ledstrip.lightLedStrip();
  // ledstrip.defaultCombo();
  // uint16_t i;
  // for(i=0; i<ledstrip.numPixels(); i++) {
  //   strip.setPixelColor(i, 255);
  //   // strip.setPixelColor(i, strip.Color(255, 255, 255));
  // }
  client.loop();
  delay(1000);
}