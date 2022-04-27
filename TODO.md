### Initial poking around
- [x] upload code to Teensy
  - [x] try moving a servo
- [x] interface with MPU-9250
- [x] interface with single point lidar

### Design
- [x] mathematically determine ideal max weight of robot
  - went off dimensions and estimate of 10oz, trying to stay near 2" max moment arm length which should be 5oz/in torque
- [x] design body for servo placement
- [x] placement of parts based on size/wiring

### Basic obstacle detection
- [ ] come up with scan pattern/rules the robot follows
- [ ] add stuck catch, based on accel values
- [ ] mark objects as boxes if the sample beams hit anything

### Telemetry
- [ ] with ESP-01 send back data to remote thing that can create 3D world of what robot perceives
### Modeling
- [ ] create 3D world/mockup of robot
- [ ] simulate the navigation
