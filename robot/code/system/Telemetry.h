// this factors both x and y accel over time
// for now it will only sample y
void moveForwardEvent()
{
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
    }

    feetPerSecond = (totalYAccelMps * 3.28) * totalWalkTimeS;
    forwardDistanceIn = feetPerSecond * 12;

    // this is bad as generally the robot is on carpet and it moves 2" per moveFoward5 command
    // it's possible it slips
    // 1.9 to encourage real numbers
    if (forwardDistanceIn < 1.9)
    {
      forwardDistanceIn = 2;
    }

    // depending on turn
    if (curAngle == 0)
    {
      if (movedForward)
      {
        robotWorldPos[1] += forwardDistanceIn;
      } else
      {
        robotWorldPos[1] -= forwardDistanceIn;
      }
    } else
    {
      float xDist = 0.0;
      float yDist = 0.0;

      xDist = cos(curAngle) * forwardDistanceIn;
      yDist = sin(curAngle) * forwardDistanceIn;

      robotWorldPos[0] += xDist;
      robotWorldPos[1] += yDist;
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

void turnLeftEvent()
{
  // radians are capped between -1 and 1, the y signage determines up/down
  // so this is not correct
  curAngle += (52 * 0.0175); // can only turn left
  // but unit circle counter-clockwise is positive direction

  // below is how you'd compute it but I'm skipping it since the accuracy
  // is so bad
  // external visual measurement is 52 deg
  // note the code below is not 100% though, wasn't matching spreadsheet

  // int prevMillis = 0;
  // float elapsedTime = 0.019; // default value based on observed median
  // int incr = 0;
  // float rotationSum = 0.0;

  // if (gyroVals.size() > 0)
  // {
  //   // elapsed time
  //   // gyro deg summed over time
  //   // negative value is counter-clockwise
  //   for (auto it = gyroVals.cbegin(); it != gyroVals.cend(); ++it)
  //   {
  //     if (incr == 0)
  //     {
  //       rotationSum = it->second * elapsedTime;
  //     } else
  //     {
  //       elapsedTime = (it->first / 1000) - (prevMillis / 1000);
  //       Serial.println(elapsedTime);
  //       rotationSum += (it->second * elapsedTime);
  //     }

  //     incr += 1;
  //     prevMillis = it->first;

  //     Serial.println(it->first);
  //   }

  //   for (auto it = gyroVals.cbegin(); it != gyroVals.cend(); ++it)
  //   {
  //     Serial.println(it->second);
  //   }

  //   Serial.println("rotation");
  //   Serial.println(rotationSum);

  //   gyroVals = {};
  // }
}

void updateTelemetry(String event)
{
  if (event == "mf")
  {
    moveForwardEvent();
  }
  else if (event == "tl")
  {
    turnLeftEvent();
  }
}

void plotCube(float size, float sweepAngle, float distance)
{
  writeToEsp("plot cube, ");
  writeToEsp(String(size) + "," + String(sweepAngle) + "," + String(distance));
}
