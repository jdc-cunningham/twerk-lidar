// using library https://github.com/gilmaimon/ArduinoWebsockets
#include <ArduinoWebsockets.h>
#include <ESP8266WiFi.h>

using namespace websockets;
WebsocketsServer socketServer;

bool clientActive = false;
int serverPollDelay = 250;

void connectToWiFi() {
  WiFi.begin("SSID", "SSIDPASS");

  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
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
  Serial.println("poll");

  if (!clientActive) {
    auto client = socketServer.accept();
    clientActive = true;
 
    if (client.available()) {
      for (int i = 0; i < 60000; i++) { // 1 minute poll for messages
        if (client.available()) {
          auto msg = client.readBlocking();
          if (msg.data().length() > 0) {
            Serial.println(msg.data());
          }
          // client.send(msg.data()); // to mobile controller
        } else {
          break;
        }
        delay(1);
      }
      clientActive = false;
    }
  }
}