void setupSerial5() {
  Serial5.begin(115200);
}

void clearSerial5()
{
  while (Serial5.available())
  {
    Serial5.read();
  }
}