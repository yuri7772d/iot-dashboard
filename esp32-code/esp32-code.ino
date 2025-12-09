#include <WiFi.h>
#include <PubSubClient.h>
#include <Adafruit_BME280.h>

WiFiClient esp;
PubSubClient mqtt(esp);
Adafruit_BME280 bme;

void setup() {
  Serial.begin(9600);
  delay(500);

  // ----- WiFi -----
  WiFi.begin("-_-","12345678"); //ssid/pass
  Serial.print("Connecting WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");

  // ----- BME280 -----
  if (!bme.begin(0x76)) {
    Serial.println("BME280 NOT FOUND!");
    while (1) delay(100);
  }
  Serial.println("BME280 OK");

  // ----- MQTT -----
  mqtt.setServer(" 10.60.160.17", 1883); //mqtt ip/port
  Serial.print("Connecting MQTT");
  while (!mqtt.connect("ESP32_Client")) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("\nMQTT connected!");
}

void loop() {

  // MQTT ต้องมี loop()**
  if (!mqtt.connected()) {
    mqtt.connect("ESP32_Client");
  }
  mqtt.loop();

  char buf[80];
  sprintf(buf, "{\"t\":%.1f,\"h\":%.1f,\"p\":%.1f}",
          bme.readTemperature(),
          bme.readHumidity(),
          bme.readPressure() /100);

  Serial.println(buf);
  mqtt.publish("/esp", buf); //mqtt topic
  delay(2000);
}
