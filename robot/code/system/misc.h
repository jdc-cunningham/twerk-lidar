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