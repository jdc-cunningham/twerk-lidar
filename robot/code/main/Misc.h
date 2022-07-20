void dumpData(bool useSerial)
{
  if (useSerial) Serial.println(gyroVals.size());

  // https://stackoverflow.com/a/14070977/2710227
  // sucks but easier to copy-paste into excel
  if (useSerial) Serial.println("s");
  for (auto it = servoPosVals.cbegin(); it != servoPosVals.cend(); ++it)
  {
    if (useSerial) Serial.println(it->first);
  }

  for (auto it = servoPosVals.cbegin(); it != servoPosVals.cend(); ++it)
  {
    if (useSerial) Serial.println(it->second);
  }

  if (useSerial) Serial.println("g");
  for (auto it = gyroVals.cbegin(); it != gyroVals.cend(); ++it)
  {
    if (useSerial) Serial.println(it->first);
  }

  for (auto it = gyroVals.cbegin(); it != gyroVals.cend(); ++it)
  {
    if (useSerial) Serial.println(it->second);
  }

  if (useSerial) Serial.println("d");
  for (auto it = depthVals.cbegin(); it != depthVals.cend(); ++it)
  {
    if (useSerial) Serial.println(it->first);
  }

  for (auto it = depthVals.cbegin(); it != depthVals.cend(); ++it)
  {
    if (useSerial) Serial.println(it->second);
  }

  Serial.println("aY");
  for (auto it = yAccelVals.cbegin(); it != yAccelVals.cend(); ++it)
  {
    if (useSerial) Serial.println(it->first);
  }

  for (auto it = yAccelVals.cbegin(); it != yAccelVals.cend(); ++it)
  {
    if (useSerial) Serial.println(it->second);
  }

  // clear here otherwise transmit using batch messaging
  if (useSerial)
  {
    gyroVals = {};
    servoPosVals = {};
    depthVals = {};
    yAccelVals = {};
    xAccelVals = {};
  }
}