String getEspSerialMsg() {
  if (ESPSERIAL.available() > 0) {
    String msg = ESPSERIAL.readString();
    clearEspSerial(); // might be redundant
    return msg;
  }

  return "";
}