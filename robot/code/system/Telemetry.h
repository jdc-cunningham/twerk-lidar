// this factors both x and y accel over time
// for now it will only sample y
void moveForwardEvent()
{
  // std::map<int, float> yAccelValsTmp = {};

  // yAccelValsTmp[9604] = -0.0665;
  // yAccelValsTmp[9627] = 0.00437;
  // yAccelValsTmp[9645] = 0.00162;
  // yAccelValsTmp[9663] = 0.04176;
  // yAccelValsTmp[9686] = 0.0345;

  if (yAccelVals.size() > 0)
  {
    int prevMillis = 0; // used for elapsed time calculation
    unsigned int extInc = 0; // dumb
    float totalWalkTimeS = 0.0; // first step assumed, median
    float totalYAccelMps = 0.0;
    float feetPerSecond = 0.0;
    int timeWalkStartMs = 0;
    float elapsedTime = 0.019;
    float forwardDistanceIn = 0.0;

    for (auto it = yAccelVals.cbegin(); it != yAccelVals.cend(); ++it)
    {
      if (extInc == 0)
      {
        timeWalkStartMs = it->first;
        totalYAccelMps += (it->second * elapsedTime);
      } else
      {
        elapsedTime = ((it->first - prevMillis) / 1000);
        elapsedTime = elapsedTime > 0.023 ? 0.019 : elapsedTime;
        totalYAccelMps += (it->second * elapsedTime);
      }

      if (extInc == yAccelVals.size() - 1)
      {
        totalWalkTimeS = (it->first - timeWalkStartMs) / 1000;
      }

      prevMillis = it->first;
      extInc += 1;

      Serial.println(it->first);
    }

    for (auto it = yAccelVals.cbegin(); it != yAccelVals.cend(); ++it)
    {
      Serial.println(it->second);
    }

    feetPerSecond = (totalYAccelMps * 3.28) * totalWalkTimeS;
    forwardDistanceIn = feetPerSecond * 12;

    Serial.println("distane in");
    Serial.println(forwardDistanceIn);

    // this is bad as generally the robot is on carpet and it moves 2" per moveFoward5 command
    // it's possible it slips
    // 1.9 to encourage real numbers
    if (forwardDistanceIn < 1.9)
    {
      forwardDistanceIn = 2;
    }

    // depending on turn
    if (movedForward)
    {
      robotWorldPos[1] += forwardDistanceIn;
    } else
    {
      robotWorldPos[1] -= forwardDistanceIn;
    }

    // send to ESP
    writeToEsp("pos update, ");
    writeToEsp(String(robotWorldPos[0]) + "," + String(robotWorldPos[1]) + "," + String(robotWorldPos[2]));

    yAccelVals = {};
  } else
  {
    Serial5.println("aY err");
  }
}

void updateTelemetry(String event)
{
  if (event == "mf")
  {
    moveForwardEvent();
  }
}
