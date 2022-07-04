void webMessaging()
{
  // poll is like a keep-alive, it bunches up due timing mismatch
  String espMsg = getEspSerialMsg().replace("poll", "");
  espMsg.replace("Hello Server!", "");

  if (espMsg)
  {
    Serial.println(espMsg);
    if (espMsg == "stop")
    {
      stopRobot = true;
    }

    // manual web-based servo control
    if (espMsg.indexOf("msc_") > -1)
    {
      manualMoveServo(espMsg);
    }

    if (espMsg.indexOf("tel_") > -1)
    {
      checkTelemetry(espMsg);
    }

    clearEspSerial();
  }

  delay(1000); // delay for sync
}