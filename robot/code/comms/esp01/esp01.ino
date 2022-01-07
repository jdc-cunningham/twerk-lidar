// using library https://github.com/gilmaimon/ArduinoWebsockets
#include <ArduinoWebsockets.h>
#include <ESP8266WiFi.h>

using namespace websockets;
WebsocketsServer socketServer;

bool clientActive = false;
int serverPollDelay = 250;

void connectToWiFi() {
  WiFi.begin("SSID", "PASS");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Waiting for connection");
  }

  Serial.println("Connected!");
  Serial.println("Starting socket server...");
  socketServer.listen(80);
}

void setup() {
  Serial.begin(115200);
  connectToWiFi();
}

void loop() {
  auto client = socketServer.accept();

  if (client.available()) {
    auto msg = client.readBlocking();
    auto msgData = msg.data();

    // write to Teensy
    if (msgData) {
      Serial.print(msgData);
    }

    // read from Teensy
    if (Serial.available()) {
      client.send(Serial.readString());
    }

    // close the connection
    client.close();
  }
  
  delay(100);
}