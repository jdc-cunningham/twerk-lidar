// this file relies on statuses.js to exist before itself

const socket = new WebSocket('ws://192.168.1.187:80'); // esp01 on robot

 // connection opened, send messages to robot
 socket.addEventListener('open', function (event) {
  socket.send('Hello Server!');
  sentMsg('Hello Server!');
  setRobotConnected(true);

  // keep connection to esp01 alive
  setInterval(() => {
    socket.send('poll');
    sentMsg('poll');
  }, 1000);
});

// listen for messages from robot
socket.addEventListener('message', function (event) {
  const robotMsg = event.data;
  receivedMsg(robotMsg);

  batteryVoltage(robotMsg);
});

