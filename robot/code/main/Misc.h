String getPrefix(String longString)
{
  if (longString == "tilt-up-2") return "t2_";
  if (longString == "tilt-up-1") return "t1_";
  if (longString == "middle") return "m_";
  if (longString == "tilt-down-1") return "d1_";
  if (longString == "tilt-down-2") return "d2_";
}

// this is in the wrong place
// this sends the servoPosVals, gyroVals and depthVals
// all tied together by time (ellapsed millis)
void sendMeshDataToWeb()
{
  bool allDataSent = false;

  writeToEsp("mtel_start");

  std::vector<String> scanTypes = {"tilt-up-2", "tilt-up-1", "middle", "tilt-down-1", "tilt-down-2"};
  // map is t2, t1, m, d1, d2
  int lastRow = 0;
  int writeCount = 0;

  for (int i = 0; i < scanTypes.size(); i++)
  {
    writeCount += 1;

    std::map<int, std::vector<float>> scanSampleTimes = scanSampleValues[scanTypes[i]];
    int joinCounter = 5; // cap to 5 (four increments)
    String msgChunk = "";

    // gives you millis time it->first
    for (auto it = scanSampleTimes.cbegin(); it != scanSampleTimes.cend(); ++it)
    {
      if (joinCounter == 5)
      {
        blueLedOn();
        writeToEsp(msgChunk);
        writeCount += 1;
        blueLedOff();
        delay(1000); // wait to send up
        joinCounter = 0;
        msgChunk = "";
      } else
      {
        joinCounter += 1;
      }

      std::vector<float> scanSampleData = it->second;
      String prefix = getPrefix(String(it->first)); // sucks call it every time vs. set/compare
      // int scanSampleLength = scanSampleData.size(); // number of scans for this sample eg. tilt-up-1
      
      msgChunk += "|"
        + prefix + String(it->first)
        + "," + String(roundUp(scanSampleData[0]))
        + "," + String(roundUp(scanSampleData[1]))
        + "," + String(roundUp(scanSampleData[2]))
        + "," + String(roundUp(scanSampleData[3]))
        + "|"; // separator
    }

    if (msgChunk != "")
    {
      writeToEsp(msgChunk); // in case any left over data
    }
  }

  writeToEsp("mtel_end");
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
  }
}