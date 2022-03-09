int batteryAnalogPin = 22; // A8

/**
 * @brief Using 100/330 ohm divider
 * 4.2V is max theoretical from single cell 18650
 * 
 * @return float 
 */
float getBatteryVoltage()
{
  int analogValue = analogRead(batteryAnalogPin);
  float dividedVoltage = ((3.223 / 1024) * analogValue);
  float correctedVoltage = ((4.2 / 3.223) * dividedVoltage);
  return correctedVoltage;
}

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
