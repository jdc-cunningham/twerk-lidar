void dumpData()
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