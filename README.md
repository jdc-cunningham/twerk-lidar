### Twerk Lidar Robot
A robot that utilizes onboard IMU and single-point lidar to navigate the world

### Sketch

<img src="./twerk-lidar-robot-concept.JPG" width="500" />

### Actual design

<img src="./devlog/media/01-07-2022--final-model.JPG" width="500">

### Disclaimer
While I have provided everything you need to make this robot, it is not intended to be rebuilt. It is too much of a pain, particularly the board soldering. Also arguable it is a waste of a Teensy 4.0 but I wanted to use one.

### Development environment

This was developed using Teensyduino so all of the libraries need to be installed there in order for the code to compile.
### Libraries used through Teensyduino IDE library search
* IMU MPU9250 (Bolderflight set, check Readme in case more added)
  * MPU9250
  * Eigen
  * Units
* ToF vl53l0x by Pololu

### Related software for this project
* Google SketchUp for the 3D modeling
* Cura for the slicer

### Related hardware
* Ender 3 Pro for the 3D printer

### About printing
The infill of prints are either 20% or 30%. I have sorted them in folders.

Pretty much anything brittle/small will be 30% or a major structural piece like the main chasis.