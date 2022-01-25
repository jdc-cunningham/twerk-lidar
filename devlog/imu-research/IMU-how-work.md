I'm reading through this 90 page paper on how to get IMUs to work.

`Manon Kok, Jeroen D. Hol and Thomas B. Sch¨on (2017), ”Using Inertial Sensors for Position and
Orientation Estimation”, Foundations and Trends in Signal Processing: Vol. 11: No. 1-2, pp 1-153.
http://dx.doi.org/10.1561/2000000094`

I will learn some of it everyday fresh brain. Will try for 30 mins at least.


### 01/24/2022 3:40 PM
Doing more reading. Not the first thing I did today but still pretty fresh, a little distracted with something.

### Page 10, ch 2

measured in terms of output voltage then converted to physical measurement

coordinate frame b of the IMU

navigation frame n (apt)

inertial frame - origin at center of earth and axes aligned with stars

earth frame - similar to inertial frame but rotates with the earth

"which coordinate frame" a vector is expressed

oh boy... "vectors can be rotated from one coordinate frame to another using a rotation matrix"

double superscript - which coordinate frame to which coordinate frame rotation is defined.

Damn I am not getting this... Fig 2.1

R^nb is the rotation matrix, vector from body frame b to the navigation frame n

Is T time? idk (unsure) -> indicates knowledge gaps

#### 2.2 angular velocity

angular velocity uses w symbol

Good lord this stuff is hard, I'm already lost basic math.

You factor in Earth's rotation (angular velocity) wie

Earth rate approximately 7.29 * 10^-5 rad/s

#### 2.3 specific force

Lol "see any textbook on dynamics" yeah I took that class 9 years ago.

#### Page 12
Yeah I'm already lost... there is too much going on here without actually trying it out/understanding it.
I will have to also use other resources.

Damn coriolis acceleration

Here is the cross product

#### 2.4 sensor errors

### 01/23/2022 8:27 PM

### Page 1
integrated, integration drifts over long time scales
algorithms including filtering
Kalman's in here

### Page 4, ch 1
orientation only vs. position

inertial sensor = 6 axes (accel and gyro)

gyroscope = angular velocity
rate of change

accel = specific force
sensor's accel and gravity

provide information on pose of subject

nice says I should be able to do this on my own, start to anyway

### Page 7
Dead-reckoning

neat there's a block diagram can be turned into a function

rotation -> orientation + accel -> subtract gravity -> accel -> pos

"white noise" signal

double integration? huh

Ooh nice link here for [dead-reckoning](https://www.allaboutcircuits.com/technical-articles/how-to-interpret-IMU-sensor-data-dead-reckoning-rotation-matrix-creation/)

Graph shows movement "drift" despite sensor sitting still on table.

In comes magnetometer for helping fight the bias/drift. Other options like GPS/UWB/Cameras.

Pose vs. orientation? Or pose as in multiple-points

non-Gaussian measurement moise