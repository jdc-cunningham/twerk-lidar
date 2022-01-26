void checkEspSerialMsg() {
  if (Serial5.available()) {
    Serial.print(Serial5.readString());
    clearSerial5();
  }
}