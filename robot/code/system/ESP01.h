void setupSerial() {
  Serial5.begin(115200);
}

void checkEspSerialMsg() {
  if (Serial5.available()) {
    Serial.print(Serial5.readString());
  }
}