#pragma config(Motor, port2, rightMotor , tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor, port3, leftMotor  , tmotorServoContinuousRotation, openLoop)
#pragma config(Motor, port4, armMotor   , tmotorServoContinuousRotation, openLoop)
#pragma config(Motor, port5, clawMotor  , tmotorServoContinuousRotation, openLoop)
#pragma config(Motor, port6, forkServo  , tmotorServoStandard          , openLoop)
#pragma config(Motor, port7, launchServo, tmotorServoStandard          , openLoop)

/*----------------------------------------------------------------------------------------------------*\
|*                                             - TEST -                                               *|
|*                                      Borrowed sample programs                                      *|
|*                                                                                                    *|
|*  This program uses a single joystick, either right or left (this is configurable below) to drive   *|
|*  the robot.                                                                                        *|
|*                                                                                                    *|
|*                                        ROBOT CONFIGURATION                                         *|
|*    NOTES:                                                                                          *|
|*    1)  Ch1 is the X axis and Ch2 is the Y axis for the RIGHT joystick.                             *|
|*    2)  Ch3 is the Y axis and Ch4 is the X axis for the LEFT joystick.                              *|
|*    3)  'abs(z)' is the ABSOLUTE VALUE of 'z'.                                                      *|
|*                                                                                                    *|
|*    MOTORS & SENSORS:                                                                               *|
|*    [I/O Port]              [Name]              [Type]              [Description]                   *|
|*    Motor - Port 2          rightMotor           VEX Motor           Right motor                    *|
|*    Motor - Port 3          leftMotor            VEX Motor           Left motor                     *|
|*    Motor - port 4          armMotor             VEX Motor           Arm motor                      *|
|*    Motor - port 5          clawMotor            VEX Motor           claw motor                     *|
|*    Motor - port 6          forkServo            VEX Servo           Fork Lift                      *|
|*    Motor - port 7          launchServo          VEX Servo           Latch release                  *|
\*----------------------------------------------------------------------------------------------------*/

void updateWheels();
void updateClaw();
void updateArm();
void updateForklift();
void updateLaunch();

const int threshold = 10;   // helps to eliminate 'noise' from a joystick that isn't perfectly at (0,0)

//+++++++++++++++++++++++++++++++++++++++++++++| MAIN |+++++++++++++++++++++++++++++++++++++++++++++++
task main ()
{
    const int update_ms = 5;

    while(true)
    {
        updateWheels();

        updateClaw();
        updateArm();

        updateLaunch();
        updateForklift();
        
        wait1Msec( update_ms );
    }
}

void updateWheels()
{

    int joy_x = vexRT[Ch1];   // This is the RIGHT analog stick.  For LEFT, change 'Ch1' to 'Ch4'.
    int joy_y = vexRT[Ch2];   // This is the RIGHT analog stick.  For LEFT, change 'Ch2' to 'Ch3'.

    // Forward, and swing turns: (both abs(X) and abs(Y) are above the threshold, and Y is POSITIVE)
    if((abs(joy_x) > threshold) && (abs(joy_y) > threshold) && (joy_y > 0))
    {
        motor[leftMotor]  = (joy_y + joy_x)/4;
        motor[rightMotor] = (joy_y - joy_x)/4;
    }
    // Backwards and swing turns: (both abs(X) and abs(Y) are above the threshold, and Y is NEGATIVE)
    else if((abs(joy_x) > threshold) && (abs(joy_y) > threshold) && (joy_y < 0))
    {
        motor[leftMotor]  = (joy_y - joy_x)/4;
        motor[rightMotor] = (joy_y + joy_x)/4;
    }

    // Turning in place: (abs(X) is above the threshold, abs(Y) is below the threshold)
    else if((abs(joy_x) > threshold) && (abs(joy_y) < threshold))
    {
        motor[leftMotor]  = joy_x;
        motor[rightMotor] = (-1 * joy_x);
    }
    // Standing still: (both abs(X) and abs(Y) are below the threshold)
    else
    {
        motor[leftMotor]  = 0;
        motor[rightMotor] = 0;
    }
}

void updateClaw()
{
    if(vexRT[Btn5U] == 1)
    {
        motor[clawMotor] = 40;
    }
    //should tighten grabber
    else if(vexRT[Btn5D] == 1)
    {
        motor[clawMotor] = -40;
    }
    // should loosen grabber
    else
        // should leave it tightened when button is relesed
    {
        motor[clawMotor] = 0;
    }
}

void updateArm()
{
    int joy1_y2 = vexRT[Ch3];

    if ( abs(joy1_y2) > threshold )
    {
        motor[armMotor] = vexRT[Ch3];     //modeled on dual joystick control and dual joystick control with arm
    }

}

bool launchToggle = false;
int lastBtn6dState = 0;

void updateLaunch()
{
    int currentBtnState = vexRT[Btn6D];

    // Only launch when last state was not pressed and current state is pressed
    if ( currentBtnState != lastBtn6dState && currentBtnState )
    {
        motor[launchServo] = launchToggle ? 100 : -100;

        // Toggle servo position
        launchToggle = !launchToggle;
    }
    lastBtn6dState = currentBtnState;
}

void updateForklift()
{
    if ( vexRT[Btn8R] )
    {
        motor[forkServo] -= 180;           //just to knock it over
    }
    //for now they just want it to be pushed over and let gravity do the rest
    else
    {
        motor[forkServo] += 60;           //resets servo back some since at 0 it starts to far forward
    }
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
