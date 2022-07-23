// this is in the wrong place
// this sends the servoPosVals, gyroVals and depthVals
// all tied together by time (ellapsed millis)
void sendMeshDataToWeb()
{
  bool allDataSent = false;

  std::vector<String, 5> scanTypes = {"tilt-up-2", "tilt-up-1", "middle", "tilt-down-1", "tilt-down-2"};
  int lastRow = 0;

  for (int i = 0; i < scanTypes.size(); i++)
  {
    std::map<int, std::vector<float>> scanSampleTimes = scanSampleValues[scanTypes[i]];

    // gives you millis time it->first
    for (auto it = scanSampleTimes.cbegin(); it != scanSampleTimes.cend(); ++it)
    {
      // https://stackoverflow.com/questions/4108313/how-do-i-find-the-length-of-an-array
      std::vector scanSampleData = it->second;
      int scanSampleLength = scanSampleData.size(); // number of scans for this sample eg. tilt-up-1
      String msgChunk = ""; // length must be <= 250

      for (int j = 0; j < scanSampleLength; j++)
      {
        // https://stackoverflow.com/questions/8581832/converting-a-vectorint-to-string
        String nextStringChunk = String(scanSampleData.begin(), scanSampleData.end());

        if (msgChunk.length() + nextStringChunk.length() >= 250)
        {
          // send what is there now
        } else
        {

        }
      }
    }
  }
}

void dumpData(bool useSerial, String scanType)
{
  if (useSerial)
  {
    Serial.println(gyroVals.size());

    // https://stackoverflow.com/a/14070977/2710227
    // sucks but easier to copy-paste into excel
    Serial.println("s");
    
    for (auto it = servoPosVals.cbegin(); it != servoPosVals.cend(); ++it)
    {
      Serial.println(it->first);
    }

    for (auto it = servoPosVals.cbegin(); it != servoPosVals.cend(); ++it)
    {
      Serial.println(it->second);
    }

    Serial.println("g");

    for (auto it = gyroVals.cbegin(); it != gyroVals.cend(); ++it)
    {
      Serial.println(it->first);
    }

    for (auto it = gyroVals.cbegin(); it != gyroVals.cend(); ++it)
    {
      Serial.println(it->second);
    }

    Serial.println("d");

    for (auto it = depthVals.cbegin(); it != depthVals.cend(); ++it)
    {
      Serial.println(it->first);
    }

    for (auto it = depthVals.cbegin(); it != depthVals.cend(); ++it)
    {
      Serial.println(it->second);
    }

    Serial.println("aY");
    for (auto it = yAccelVals.cbegin(); it != yAccelVals.cend(); ++it)
    {
      Serial.println(it->first);
    }

    for (auto it = yAccelVals.cbegin(); it != yAccelVals.cend(); ++it)
    {
      Serial.println(it->second);
    }

    gyroVals = {};
    servoPosVals = {};
    depthVals = {};
    yAccelVals = {};
    xAccelVals = {};
  } else
  {
    if (scanType == "tilt-down-2") // last one
    {
      sendMeshDataToWeb();
    }
  }
}