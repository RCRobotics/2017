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
void updateWheel(float scaler, int joystickChannel, int motorId);
void updateClaw();
void updateArm();
void updateLaunch();
bool updateToggle(int buttonId, int* lastButtonState);


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

int lastBtn8LState = 0;

void updateWheels()
{
	const float scaler = 0.75;

	//TODO determine scalar

	bool toggleState = updateToggle(Btn8L, &lastBtn8LState);

	// Update left wheel
	updateWheel(scaler, Ch3, leftMotor);
	// Update right wheel
	updateWheel(scaler, Ch2, rightMotor);
}

void updateWheel(float scaler, int joystickChannel, int motorId)
{
	// If the joystick is greater than or less than the threshold
	if(abs(vexRT[joystickChannel]) > threshold)
	{
	  motor[motorId]  = (float)vexRT[joystickChannel] * scaler;
	}
	// If the joystick is within the threshold
	else
	{
		// Stop the motor (cancel noise)
	  motor[motorId]  = 0;
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

bool updateToggle(int buttonId, int* lastButtonState)
{
	//TODO
	*lastButtonState = 100;

	return true;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
