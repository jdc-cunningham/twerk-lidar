// this is using serial commands
// translted from these python scripts
// https://github.com/jdc-cunningham/slam-crappy/blob/master/pi/system/lidar_sensor.py
// original https://www.raspberrypi.org/forums/viewtopic.php?f=91&t=261501&sid=bd5a2075068a119ae047064d2fb299d4#p1594877

#include <vector>
#include <numeric>

#define TFMINISSERIAL Serial3

void setupTFminiS()
{
  TFMINISSERIAL.begin(115200);
}

float getTFminiSDistance()
{
  TFMINISSERIAL.print(0x42); // bytes(b'B')
  TFMINISSERIAL.print(0x57); // bytes(b'w')
  TFMINISSERIAL.print(0x02); // bytes(2)
  TFMINISSERIAL.print(0x00); // bytes(0)
  TFMINISSERIAL.print(0x00);
  TFMINISSERIAL.print(0x00);
  TFMINISSERIAL.print(0x01); // bytes(1)
  TFMINISSERIAL.print(0x06); // bytes(6)

  bool samplingComplete = false;
  int sampleCount = 0;
  int maxSampleCount = 30;
  std::vector<float> samples;

  while (!samplingComplete)
  {
    if (TFMINISSERIAL.available() >= 9)
    {
      if (TFMINISSERIAL.read() == 89 && TFMINISSERIAL.read() == 89) // b'Y'
      {
        int Dist_L = TFMINISSERIAL.read();
        int Dist_H = TFMINISSERIAL.read();
        float Dist_Total = (Dist_H * 256) + Dist_L;

        // not sure why this code is like this
        // clears buffer? returns same thing
        for (int i = 0; i < 5; i++)
        {
          TFMINISSERIAL.read();
          samples.push_back(Dist_Total);
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
