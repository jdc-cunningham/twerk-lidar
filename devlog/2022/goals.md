### Bare minimum working mapping and navigation
- [ ] Robot system
  - [x] fix pitch up/down because angle sampling is not good due to vibration
  - [ ] get pitch angle from NED, hopefully better than gyro
  - [ ] finish basic obstacle math using 3D collision checking
  - [ ] track linear acceleration and rotation
- [ ] ThreeJS visualizer
  - [ ] function to draw and place cubes
  - [ ] Draw robot cube for now/can update later with actual robot `glTF` file
  - [ ] receive transmitted obstacle cube dimensions, locations and plot
- [ ] Misc
  - [ ] add battery check, when exhausted release servos so it collapses on its
        on weight and then flash the blue LED/notify web
        use `servo.detach()` need to make sure that doesn't make it go
        crazy/strip itself
