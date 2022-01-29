void setupBlueLed()
{
  pinMode(23, OUTPUT);
}

void blueLedOn()
{
  digitalWrite(23, HIGH);
}

void blueLedOff()
{
  digitalWrite(23, LOW);
}

void blueLedBlink(int times = 1)
{
  for (int i = 0; i < times; i++)
  {
    digitalWrite(23, HIGH);
    delay(100);
    digitalWrite(23, LOW);
    delay(100);
  }
}