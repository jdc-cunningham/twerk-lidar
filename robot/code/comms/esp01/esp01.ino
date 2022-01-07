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

void clearSerial()
{
  while (Serial.available())
  {
    Serial.read();
  }
}

void setup() {
  Serial.begin(115200);
  connectToWiFi();
} 

// void loop() {
//   auto client = socketServer.accept();

//   if (client.available()) {
//     auto msg = client.readBlocking();

//     // write to Teensy
//     if (msg.data()) { // two runs
//       Serial.print(msg.data());
//     }

//     // read from Teensy
//     if (Serial.available()) {
//       client.send(Serial.readString());
//       // clearSerial();
//     }

//     // close the connection
//     // client.close();
//   }
  
//   delay(100);
// }

void loop() {
  Serial.print("loop");
  // Serial.print(WiFi.status());
  // if (!clientActive) {
    auto client = socketServer.accept();
  //   clientActive = true;
 
    if (client.available()) {
  //     for (int i = 0; i < 60000; i++) { // 1 minute poll for messages
  //       client.send("loop");
  //       if (client.available()) {
          auto msg = client.readBlocking();
          if (msg.data().length() > 0) {
            Serial.print(msg.data());
          }

          client.send("yo");
          client.close();

  //         if (Serial.available()) {
  //           Serial.print("send");
  //           client.send(Serial.readString());
  //           // clearSerial();
  //         }

          // client.send(msg.data()); // to mobile controller
  //       } else {
  //         break;
  //       }
  //       delay(1);
  //     }
  //     clientActive = false;
    }
  // }
  delay(100);
}
