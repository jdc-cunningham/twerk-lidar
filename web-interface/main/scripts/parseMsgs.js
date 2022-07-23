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

// https://stackoverflow.com/a/54984389/2710227
const roundTo2 = (val) => Math.round(val * 100) / 100;
const roundTo3 = (val) =>  Math.round(val * 1000) / 1000;

const meshPlot = (meshTelData) => {
  const meshTelData1 = meshTelData.replace('mtel_start', ''); // I'm just getting this done at this point 8hrs in
  const meshTelData2 = meshTelData1.replace('mtel_end', '');
  const meshData = meshTelData2.split('|');

  const meshGroups = {};
  const meshGroupKeys = [];
  let activeGroup = "";

  meshData.forEach(strPart => {
    if (strPart.indexOf('tilt-') !== -1 || strPart.indexOf('middle') !== -1) {
      activeGroup = strPart;
      meshGroups[strPart] = [];
      meshGroupKeys.push(strPart);
    } else {
      if (strPart.trim()) {
        meshGroups[activeGroup].push(strPart.replace('\n', '').split(','));
      }
    }
  });

  // process the data for the mesh plot
  // this is lazy code

  /**
   * time to seconds
   * compute elapsed seconds between rows should be the same
   * multiply gyro/sec with elapsed seconds
   * sum the gyro deg/sec per motion captured
   */

  const finalData = {};

  // prefil
  meshGroupKeys.forEach(key => finalData[key] = []);

  // convert comma-separated string to separate int/floats
  // get the seconds
  meshGroupKeys.forEach(key => {
    meshGroups[key].forEach(data => {
      finalData[key].push([
        parseInt(data[0]),
        parseInt(data[0])/ 1000,
        parseFloat(data[1]),
        parseFloat(data[2]),
        parseFloat(data[3]),
        parseFloat(data[4])
      ]);
    });
  });

  // get elapsed time
  // they're pretty much all the same so just sample one
  const elapsedTime = roundTo3(finalData[meshGroupKeys[0]][1][1] - finalData[meshGroupKeys[0]][0][1]); // note the 2nd row - 1st row

  const finalData1 = {}; // lol

  meshGroupKeys.forEach(key => {
    finalData1[key] = [];

    finalData[key].forEach(data => {
      finalData1[key].push([
        data[1],
        data[2],
        roundTo2(data[3] * elapsedTime),
        data[4],
        data[5]
      ]);
    });
  });

  const finalData2 = {};

  // sum the gyro vals, oof this is where algos would be good or structures
  meshGroupKeys.forEach(key => {
    finalData2[key] = [];

    let accumulator = 0;

    finalData1[key].forEach(data => {
      if (data[1] === 0) {
        accumulator = 0;
      }

      accumulator += data[2];

      finalData2[key].push([
        data[0],
        data[1],
        roundTo2(data[2] + accumulator),
        data[3],
        data[4]
      ]);
    });
  });

  // the keys here don't 100% match the above
  const sensorSamples2 = {
    "tilt-up-2": {
      "angle": 18.5,
      "sweep-angles":"",
      "tof-samples": ""
    },
    "tilt-up-1": {
      "angle": 11.4,
      "sweep-angles":"",
      "tof-samples": ""
    },
    "level": {
      "angle": 1.6,
      "sweep-angles":"",
      "tof-samples": ""
    },
    "tilt-down-1": {
      "angle": -8.8,
      "sweep-angles":"",
      "tof-samples": ""
    },
    "tilt-down-2": {
      "angle": -16.8,
      "sweep-angles":"",
      "tof-samples": ""
    }
  };

  console.log(finalData2);

  meshGroupKeys.forEach(key => {
    let gyroAngles = "";
    let tofRanges = "";

    finalData2[key].forEach((data, index) => {
      if (index === 0) {
        gyroAngles = data[2].toString();
        tofRanges = data[3].toString();
      } else {
        gyroAngles += "\n" + data[2].toString();
        tofRanges += "\n" + data[3].toString();
      }
    });

    if (key === "middle") {
      sensorSamples2["level"]["sweep-angles"] = gyroAngles;
      sensorSamples2["level"]["tof-samples"] = tofRanges;
    } else {
      sensorSamples2[key]["sweep-angles"] = gyroAngles;
      sensorSamples2[key]["tof-samples"] = tofRanges;
    }
  });

  // inherited from index.html
  sensorSamples = {...sensorSamples2};
  console.log(sensorSamples);
  threejsPlotChart();
}