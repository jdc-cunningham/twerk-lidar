### The world coordinate system

Ha fancy name. The premise of this robot is it can track itself using the onboard IMU and it can probe the world with the single-point ToF "lidar" sensor. It is single point, so that's where the "twerking" comes in. It will shift its joints around to form a conical sampling section to see what's in front of it. Of course this is a very crude way to sense your surroundings. The main goals are:

* avoid big obstacles
* avoid falling
* react to problems eg. falling

Since I'm working with servos this robot is crude but I'm also crude myself with regard to my current knowledge of this space.

I am aware moving all joints to take measurements vs. say a pan/tilt (2) servo system is not a great design in terms of saving energy but this whole project aside from being a gimmick is a learning experience for me.

