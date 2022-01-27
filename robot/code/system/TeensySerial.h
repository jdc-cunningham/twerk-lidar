#define ESPSERIAL Serial5

void setupEspSerial() {
  ESPSERIAL.begin(115200);
}

void clearEspSerial()
{
  while (ESPSERIAL.available() > 0)
  {
    ESPSERIAL.read();
  }
}