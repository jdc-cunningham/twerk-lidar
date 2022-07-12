const setRobotConnected = (isConnected) => {
  const statusIndicator = document.getElementById('connected-indicator');
  const statusIndicatorText = document.getElementById('connected-indicator-text');

  if (isConnected) {
    statusIndicator.style.backgroundColor = 'green';
    statusIndicatorText.innerText = 'Connected';
  } else {
    statusIndicator.style.backgroundColor = 'gray';
    statusIndicatorText.innerText = 'Lost connection, reconnecting...';
  }
}