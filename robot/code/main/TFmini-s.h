// this is using serial commands
// translted from these python scripts
// https://github.com/jdc-cunningham/slam-crappy/blob/master/pi/system/lidar_sensor.py
// original https://www.raspberrypi.org/forums/viewtopic.php?f=91&t=261501&sid=bd5a2075068a119ae047064d2fb299d4#p1594877

#include <vector>
#include <numeric>

#define TFMINI_S_SERIAL Serial3

void setupTFminiS()
{
  TFMINI_S_SERIAL.begin(115200);
}

float getTFminiSDistance()
{
  TFMINI_S_SERIAL.print(0x42); // bytes(b'B')
  TFMINI_S_SERIAL.print(0x57); // bytes(b'w')
  TFMINI_S_SERIAL.print(0x02); // bytes(2)
  TFMINI_S_SERIAL.print(0x00); // bytes(0)
  TFMINI_S_SERIAL.print(0x00);
  TFMINI_S_SERIAL.print(0x00);
  TFMINI_S_SERIAL.print(0x01); // bytes(1)
  TFMINI_S_SERIAL.print(0x06); // bytes(6)

  bool samplingComplete = false;
  int sampleCount = 0;
  int maxSampleCount = 5; // tried this at 5, got bad values like 30, 284033, 14540... etc, but bumping up to 30 made it work as expected
  std::vector<float> samples;

  while (!samplingComplete)
  {
    if (TFMINI_S_SERIAL.available() >= 9)
    {
      if (TFMINI_S_SERIAL.read() == 89 && TFMINI_S_SERIAL.read() == 89) // b'Y'
      {
        int Dist_L = TFMINI_S_SERIAL.read();
        int Dist_H = TFMINI_S_SERIAL.read();
        float Dist_Total = (Dist_H * 256) + Dist_L;

        Serial.println(Dist_Total);

        // not sure why this code is like this
        // clears buffer? returns same thing
        for (int i = 0; i < 5; i++)
        {
          TFMINI_S_SERIAL.read();
          if (Dist_Total < 999) // need to consider adding a guard like this for bad values or have a cap based on max scan interest
          {
            samples.push_back(Dist_Total);
          }
        }

        sampleCount += 1;

        if (sampleCount == maxSampleCount)
        {
          samplingComplete = true;
        }
      }
    }
  
    delay(1);
  }

  // https://stackoverflow.com/questions/28574346/find-average-of-input-to-vector-c
  return accumulate(samples.begin(), samples.end(), 0.0) / samples.size();
}
