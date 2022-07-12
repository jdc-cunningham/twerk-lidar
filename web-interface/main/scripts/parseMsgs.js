const batteryVoltage = (robotMsg) => {
  if (robotMsg.indexOf('bv_') !== -1) {
    // const voltageDisplay = document.getElementById('voltage-display');
    // voltageDisplay.innerText = robotMsg.split('bv_')[1];
  }
}

const upsideDown = (robotMsg) => {
  if (robotMsg.indexOf('e_ud') !== -1) {
    setRobotIsUpsideDown(true);
  }
}