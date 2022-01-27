String checkEspSerialMsg() {
  if (Serial5.available()) {
    String msg = Serial5.readString();
    clearSerial5(); // might be redundant
    return msg;
  }

  return "";
}