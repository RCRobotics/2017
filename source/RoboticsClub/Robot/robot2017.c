#pragma config(Motor, port2, rightMotor , tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor, port3, leftMotor  , tmotorServoContinuousRotation, openLoop)
#pragma config(Motor, port4, armMotor   , tmotorServoContinuousRotation, openLoop)
#pragma config(Motor, port5, clawMotor  , tmotorServoContinuousRotation, openLoop)
#pragma config(Motor, port6, launchServo, tmotorServoStandard          , openLoop)

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
|*    Motor - port 6          launchServo          VEX Servo           Latch release                  *|
\*----------------------------------------------------------------------------------------------------*/

void updateWheels();
void updateClaw();
void updateArm();
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

		wait1Msec( update_ms );
	}
}

void updateWheels()
{

	const float scaler = 0.75;

	if(abs(vexRT[Ch3]) > threshold)         // If the left joystick is greater than or less than the threshold:
	{
	  motor[leftMotor]  = (float)vexRT[Ch3] * scaler;
	}
	else                                    // If the left joystick is within the threshold:
	{
	  motor[leftMotor]  = 0;                // Stop the left motor (cancel noise)
	}

	if(abs(vexRT[Ch2]) > threshold)         // If the right joystick is greater than or less than the threshold:
	{
		motor[rightMotor]  = (float)vexRT[Ch2] * scaler;
	}
	else                                    // If the right joystick is within the threshold:
	{
	  motor[rightMotor] = 0;                // Stop the right motor (cancel noise)
	}
}

bool Btn5UToggle = false;

void updateClaw()
{
	if(vexRT[Btn5U] == 1)
	{
	  // should leave it tightened when button is relesed
		motor[clawMotor] = -100;
		Btn5UToggle = true;
	}
	//should tighten grabber
	else if(vexRT[Btn5D] == 1)
	{
		motor[clawMotor] = 100;
		Btn5UToggle = false;
	}
	else if (vexRT[Btn5D] != 1 && Btn5UToggle == false)
	{
  	// should loosen grabber
		motor[clawMotor] = 0;
	}
}

void updateArm()
{
	const int armSpeed = 100;

	//Btn6U for arm up
	if (vexRT[Btn6U] == 1)
	{
		motor[armMotor] = armSpeed;
	}
	//Btn6D for arm Down
	else if (vexRT[Btn6D] == 1)
	{
		motor[armMotor] = -armSpeed;
	}
	else
	{
		motor[armMotor] = 0;
	}
}

bool launchToggle = false;
int lastBtn6dState = 0;

void updateLaunch()
{
	int currentBtnState = vexRT[Btn8D];

	// Only launch when last state was not pressed and current state is pressed
	if ( currentBtnState != lastBtn6dState && currentBtnState )
	{
		motor[launchServo] = launchToggle ? 180 : -180;

		// Toggle servo position
		launchToggle = !launchToggle;
	}
	lastBtn6dState = currentBtnState;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
