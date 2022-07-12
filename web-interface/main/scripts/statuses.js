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

// the robot will stop on its own
const setRobotIsUpsideDown = () => {
  const upsideDownModal = document.getElementById('upside-down-modal');
  upsideDownModal.classList = '';

  const dismissBtn = document.getElementById('dismiss-upside-down-modal');

  dismissBtn.addEventListener('click', () => {
    upsideDownModal.classList = 'hidden';
  });
}