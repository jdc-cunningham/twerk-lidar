### Scott Lobdell 13mins
I've awatched this [one](https://www.youtube.com/watch?v=T9jXoG0QYIA) before but I'll really pay attention this time

I think I might try something today where I transmit the computed values by the ESP-01 to a ThreeJS plotter on a 3D coordinate system.

That could be interesting. I don't have too much time but I can put down like an hour or two.

Each axis is a vector.

#### step 1
- calibrate magnetometer
  - rotate in all directions
  - plot some points
  - ideally perfect sphere
  - shift median, median x/y/z over time, apply offset

#### step 2 - pass into AHRS
rotation matrix (ah)

One AHRS is Madgwick Quaternion Update

Quaternion update (w, x, y, z)

Quaternion -> pitch, roll, yaw (magnetic declanation offset - true north)

Some value, mag dec offset

Change acceleration to NED

Matrix multiplication

Looks familiar [3x3] x [3x1] from that allaboutcircuits math

I see the [0, 0, 1] now from aac again

You get ax, ay, az

Get NED

Remove gravity from acceleration, get absolute terms

Video ended

I'm trying to find this other one I was trying to follow along

### Matlab 16mins
Yeah this is the [one](https://www.youtube.com/watch?v=0rlvvYgmTvI) keep starting/stoppping it.

AHRS - attitude and heading reference system

This looks like a good link, it's for [Arduino](https://www.mathworks.com/help/fusion/ug/Estimating-Orientation-Using-Inertial-Sensor-Fusion-and-MPU-9250.html) too

Direction cosine matrix (DCM)

Three-dimensional rotation between two different coordinate frames.

I think I can picture that, robot vs. the apt room

Find absolute orientation using mag and accel, use gyro to correct for errors when system is moving (need)

This video uses NED as well.

Magnetic north can point downards towards the ground vs. up to the North pole

Looking at this math tutorial [lol](https://www.mathsisfun.com/algebra/vectors-cross-product.html) noob

Two vectors can be multiplied using cross product

Cross product results in a new vector that has right angles to both the other two vectors. Magnetitude ... area of parallelogram

If the two vectors point in same direction the cross product is 0 in length

Oh yeah wait... the aac source used something similar except it's dot product

`a x b = |a| |b| sin(theta) n`

Dot product gets scalar answer

Two ways to calculate cross the above and also using standard math (lol)

eg.

cx = aybz - azby;
cy = azbx - axbz;
cz = axby - aybx;

Back to video at 4:01

Measured mag (pointing into Earth) and measured accel.

Orientation of body is rotation between body frame and NED frame.

DCM visualization works but has problems.

Down is affected by motion of the accel.

Magnetic disturbance also affects it

Hard and soft iron sources

Hard - permanent or coil, rotate mag, circle, offset from origin

Soft - magnetic like a nail, ferous

Affects measurement turns it into a circle vs. oval

#### 8:17 Mag calibration

Magnetic field vector would trace out a perfect sphere around IMU if no disturbances

Measure distortion and calibrate, transformation matrix and bias

Phone asks this before using a compass, spin in directions

#### 9:45 corrupting linear accelerations

Cool it's talking about expected movement vs. real.

Can throw out accel values that are too high, while the robot is walking maybe

### 11:20 adding gyro

I think this video is the one that is the most helpful. Like I can actually build what I want with this video.

measured angular rate multiply by time to get change in angle over time

Dead reckoning

Integrating gyro measurement

Integration is like a low pass filter

High frequency noise smoothed out.

accel + mag provides initial orientation and gyro provides changes

Apply filters to join, complementary, kalman, madgwick mahony

Init attitude, use mag field and gravity to correct gyro drift

### 13:55 blending overview
Correct back to absolute

complementary decide your needs

Kalman filter, optimal gain calculated for you, noise, how good

Fancy averaging between two solutions

