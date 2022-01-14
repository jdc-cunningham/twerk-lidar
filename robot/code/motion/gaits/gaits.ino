/**
 * top view of servos
 * 
 *    FLO                      FRO
 *         FLM            FRM
 *              FLI  FRI
 * 
 * 
 *              BLI  BRI
 *         BLM            BRM
 *    BLO                      BLO
 */
#include "ServoMovements.h"

// ex call
// servoGroupArr[][3] = {
//   {#, #, #}
//   {#, #, #}
//   {#, #, #}
//   {#, #, #}    
// }

void turnLeft()
{
  // move back-left leg up

  // move front-right leg back
  // move back-left leg down
  // move back-right leg up
  // move front-left leg forward
  // move back-right leg down
}

void level()
{

}

void setup()
{
  setAndCenterServos();
  delay(5000);
  // moveForward();
  // moveForward2();
  // delay(1000);
  // level();
}

void loop()
{
  // moveForward();
}