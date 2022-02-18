// sweep goes from top-left to top-right
// A B C
// D E F
// G H I

// end result will be four planes/meshes comprised of:
// A  B   B  C
//
// D  E   E  F
// 
// D  E   E  F
//
// G  H   H  I

// key is the tilt angle, values are at sweep
// center is not skipped and measurements are mirrored so values are in pattern of 3, 5, 7, etc...
// const sampleCluSensorValues = {
//   "10": [22.67, 22.34, 22.67],
//   "0": [22.34, 22, 22.34],
//   "-10": [22.67, 22.34, 22.67]
// };

// https://www.w3resource.com/javascript-exercises/javascript-math-exercise-33.php
const degreesToRadians = (degrees) => {
  const pi = Math.PI;
  return degrees * (pi/180);
}

const getXCoordinate = (sweepAngle, distance) => {
  const distanceRadians = degreesToRadians(Math.abs(parseInt(sweepAngle)));
  const xCoordinate = parseFloat((distance * Math.sin(distanceRadians)).toFixed(2));
  return sweepAngle > 0
    ? xCoordinate
    : xCoordinate * -1;
}

const getYCoordinate = (sweepAngle, distance) => {
  const distanceRadians = degreesToRadians(Math.abs(parseInt(sweepAngle)));
  return parseFloat((distance * Math.cos(distanceRadians)).toFixed(2));
}

const getZCoordinate = (tiltAngle, distance, offset = 0) => {
  const distanceRadians = degreesToRadians(Math.abs(parseInt(tiltAngle)));
  let zCoordinate = parseFloat((distance * Math.sin(distanceRadians)).toFixed(2));
  zCoordinate += offset;

  return tiltAngle >= 0
    ? zCoordinate
    : zCoordinate * -1;
}

