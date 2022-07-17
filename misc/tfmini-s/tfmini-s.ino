// this is using serial commands
// translted from these python scripts
// https://github.com/jdc-cunningham/slam-crappy/blob/master/pi/system/lidar_sensor.py
// original https://www.raspberrypi.org/forums/viewtopic.php?f=91&t=261501&sid=bd5a2075068a119ae047064d2fb299d4#p1594877

#define TFMINISSERIAL Serial3

void setupTFminiSSerial()
{
  TFMINISSERIAL.begin(115200);
}

void setup()
{
  Serial.begin(115200);
  Serial.println("setup");
  TFMINISSERIAL.begin(115200);
}

void getTofDistance()
{
  TFMINISSERIAL.print(0x42); // bytes(b'B')
  TFMINISSERIAL.print(0x57); // bytes(b'w')
  TFMINISSERIAL.print(0x02); // bytes(2)
  TFMINISSERIAL.print(0x00); // bytes(0)
  TFMINISSERIAL.print(0x00);
  TFMINISSERIAL.print(0x00);
  TFMINISSERIAL.print(0x01); // bytes(1)
  TFMINISSERIAL.print(0x06); // bytes(6)

  bool gotMeasurement = false;

  while (!gotMeasurement)
  {
    if (TFMINISSERIAL.available() >= 9)
    {
      if (TFMINISSERIAL.read() == 89 && TFMINISSERIAL.read() == 89) // b'Y'
      {
        Serial.println("match");
        int Dist_L = TFMINISSERIAL.read();
        int Dist_H = TFMINISSERIAL.read();
        float Dist_Total = (Dist_H * 256) + Dist_L;

        // not sure why this code is like this
        // clears buffer? returns same thing
        for (int i = 0; i < 5; i++)
        {
          TFMINISSERIAL.read();
          Serial.println(Dist_Total);
        }

        gotMeasurement = true;
      }
    }
    delay(1);
  }
}

void loop()
{
  getTofDistance();
  delay(1000);
}