
### 01/23/2022
Initial thoughts before I put in the studying. Will answer this when I know.

### How do you estimate rotation from an IMU in all 3 axes?

In particular what I need to know is the tilt/sweep. It looks like you could kind of pull tilt with gravity but horizontal turning not so much.

Also the concern of drift and since this is a rickity robot, trying to avoid vibrations affecting estimates would be nice.

Right now I have no idea... I see things that kinda look familiar, big parenthesis with things in them... but what do you do?

I think you grab sample data with elapsed time (don't know how to use a clock yet on Arduino).

Then create a graph from those points somewhow and integrate it? Idk...