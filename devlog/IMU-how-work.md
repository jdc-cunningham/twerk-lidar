I'm reading through this 90 page paper on how to get IMUs to work.

`Manon Kok, Jeroen D. Hol and Thomas B. Sch¨on (2017), ”Using Inertial Sensors for Position and
Orientation Estimation”, Foundations and Trends in Signal Processing: Vol. 11: No. 1-2, pp 1-153.
http://dx.doi.org/10.1561/2000000094`

I will learn some of it everyday fresh brain. Will try for 30 mins at least.

### 01/23/2022 8:27 PM

#### Page 1
integrated, integration drifts over long time scales
algorithms including filtering
Kalman's in here

#### Page 4, ch 1
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

### Page 10, ch 2