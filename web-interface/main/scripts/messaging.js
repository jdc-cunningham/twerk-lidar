const sentTab = document.getElementById('sent-tab');
const receivedTab = document.getElementById('received-tab');
const sentDisplay = document.getElementById('sent-msgs-disp');
const receivedDisplay = document.getElementById('received-msgs-disp');
const clearDispBtn = document.getElementById('clear-active-tab');

const sentMsg = (msg) => {
  sentDisplay.value += msg + `\r\n`;
}

const receivedMsg = (msg) => {
  receivedDisplay.value += msg + `\r\n`;
}

let activeTab = 'sent';

const toggleTabs = (setTab) => {
  if (setTab === 'sent') {
    receivedTab.classList = '';
    receivedDisplay.classList = 'hidden';
    sentTab.classList = 'active';
    sentDisplay.classList = '';
    activeTab = setTab;
  } else {
    sentTab.classList = '';
    sentDisplay.classList = 'hidden';
    receivedTab.classList = 'active';
    receivedDisplay.classList = '';
    activeTab = setTab;
  }
}

sentTab.addEventListener('click', () => {
  toggleTabs('sent');
});

receivedTab.addEventListener('click', () => {
  toggleTabs('received');
});

clearDispBtn.addEventListener('click', () => {
  if (activeTab === 'sent') {
    sentDisplay.value = '';
  } else {
    receivedDisplay.value = '';
  }
});