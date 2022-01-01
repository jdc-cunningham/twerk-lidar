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
  // Serial.println("poll");

  auto client = socketServer.accept();

  if (client.available()) {
    auto msg = client.readBlocking();

    // ping Teensy
    Serial.print(msg.data());

    if (Serial.available()) {
      client.send(Serial.readString());
    }

    // log
    // Serial.print("Got Message: ");
    // Serial.println(msg.data());

    // return echo
    // client.send("Echo: " + msg.data());

    // close the connection
    client.close();
  }
  
  delay(1000);
}