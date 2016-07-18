#include "MotorControl.h"
#include "motor_pcb_interface.h"
#include "math.h"

/*******************************  return the speed  *************************************/
// global parameter to set the speed
// when we want to set a speed we could change this parameter
static int16_t currentSettedSpeed;

void setSpeed(int16_t speed)
{
	currentSettedSpeed = speed;
}
int16_t returnSpeed()
{
	return currentSettedSpeed;
}

/******************************************************************************************/

/*****************************   return the angle difference  ****************************/
// global parameter to return the angle
static int16_t currentAngleDifference = 0;
int16_t returnAngle(void)
{
		return currentAngleDifference;
}

/******************************************************************************************/

/*
* so easy!!
*/
int16_t myABS(int16_t value)
{
	if(value >= 0)
		return value;
	else 
		return -value;
}

/*
* constrain the variation between MAX and MIN
*/
int16_t constrain(int16_t input, int16_t min, int16_t max)
{
	if(input > max)
		input = max;
	else if(input < max)
		input = min;
	return input;
}

/*
* constrain the variation between -180 to 180
*/
int16_t constrain2(int16_t input)
{
	if(input < -360)
		input = input % -360;
	else if(input > 360)
		input = input %360;
	
	if(input < -180)
		input = 360 + input;
	else if(input > 180)
		input = input - 360;
	return input;
}

/*
* this function can calculate the angle difference between -180 to 180, and when we reach the jump point, we can also get a right result
*/
int16_t calculateAngleDifference(int16_t angle1, int16_t angle2)
{
		if(angle1 - angle2 < -180)
		{
			angle2 = -180 - (180 - angle2);
			return (angle1 - angle2);
		}
		else if(angle1 - angle2 > 180)
		{
			angle2 = 180 + (angle2 + 180);
			return (angle1 - angle2);
		}
		else
			return (angle1 - angle2);
}

/*
* convert the angle from -180~180 to 0~360
*/
int16_t angleTransform(int16_t angle_ABS180)
{
	if(angle_ABS180 > 0)
		return angle_ABS180 % 360;
	else
		return (360 + angle_ABS180) % 360;
}

/*
* using PID to set the speed, we should keep the trail a straight line
* so we should read the current speed every 30ms and run the PID controller function every 30ms
* the correction of PID is the speed difference, so when we set the speed using API,
* we need to plus the correction with a const speed which we received 
*/

static int16_t LastError = 0;     // global error [-1]
static int16_t PrevError = 0;     // global error [-2]
int16_t MotorSpeedPID(int16_t speed)
{
	// get current speed from conuter
	uint16_t leftSpeed   = Get_Speed(LEFT);
	uint16_t rightSpeed = Get_Speed(RIGHT);

	double Proportion = P_DATA_SPEED;  // Proportional Const
  double Integral     = I_DATA_SPEED;  // Integral Const
  double Derivative  = D_DATA_SPEED;  // Derivative Const

	// current error, we use left - right to represent the speed
	int16_t speedDiffernrce = leftSpeed - rightSpeed;

  // delta calculation     
  int16_t correctionSpeed = Proportion   * (speedDiffernrce -  LastError)                          // E[k]
                                        + Integral    *  speedDiffernrce                                             // E[k-1]
                                        + Derivative * (speedDiffernrce - 2 * LastError + PrevError);     // E[k-2]
  PrevError = LastError; 
  LastError = speedDiffernrce;

  // make sure that the speed is larger than zero
	if(speed - correctionSpeed < 0)
		leftSpeed = 0;
	else
		leftSpeed = speed - correctionSpeed;
	
	if(speed + correctionSpeed < 0)
		rightSpeed = 0;
	else
		rightSpeed = speed + correctionSpeed;

  // implenment the PID settings
  Motor_Set_Speed(LEFT, leftSpeed);
  Motor_Set_Speed(RIGHT, rightSpeed);
	return correctionSpeed;
}

/*
* use increment PID, before we reach the setted angle, we will keep calculating
* after seting angle, we will call another function to set the speed
* 
* positive angle means anti-clock-wise
* negative angle means clock-wise
*/
static int16_t AngleLastError  = 0;             // Error [-1]
static int16_t AnglePrevError  = 0;             // Error [-2]
void Motor_Move(int16_t angle, u8 if_related, int16_t speed)
{
		double Proportion = P_DATA_ANGLE;  // Proportional Const
		double Integral     = I_DATA_ANGLE;    // Integral Const
		double Derivative  = D_DATA_ANGLE;  // Derivative Const
		u16 i = 0;
		int temp = 0; 
		int max = 0; 
		int min = 200;
	
		// make sure that we get a right angle, sometimes this function will return zero which is a wrong number
		// the larger the value is the true value we will get
		int16_t angleNow;
		int16_t angleSet;

	  /************************  make syre we get the right angle  ************************/
		for(;i < 700;i++)
			angleNow = Inertia_Get_Angle_Yaw();
	  /*****************************************************************************************/
	
		// this angle has been contrained between -180 to 180
		angleSet = constrain2(if_related ? (angleNow + angle) : angle);
		
		// a loop to turn the angle setted
		// △u(k)=Kp[e(k)-e(k-1)]+Kie(k)+Kd[e(k)-2e(k-1)+e(k-2)]
		// △u(k)=Ae(k)-Be(k-1)+Ce(k-2)
		while(myABS(calculateAngleDifference(angleSet, angleNow)) > ACCEPTTED_ERROR_ANGLE)
		{
				// current error and the correction
				int16_t currentError, correctionAngle;
				int i = 0;
				// angleSet - angle Now
				currentError = calculateAngleDifference(angleSet, angleNow);
				
				/***********************************   UART debug  *********************************************/
				currentAngleDifference = currentError;
				/**************************************************************************************************/
			
				// delta calculation     
				correctionAngle = Proportion  * (currentError - AngleLastError)                                           // E[k]              
														     + Integral      * AngleLastError                                                                // E[k-1]
																 + Derivative  * (AnglePrevError - 2*AngleLastError + AnglePrevError)          // E[k-2] 
			                           + 50;

				PrevError = LastError;     // save last error, for next usage 
				LastError = currentError;

				// implement
				// right and less than 180 degree, so we directly turn the angle difference
				if(correctionAngle > 0)
				{
					Motor_If_Forward(RIGHT, 0);
					Motor_If_Forward(LEFT, 1);

					Motor_Set_Speed(LEFT, myABS(correctionAngle)); 
					Motor_Set_Speed(RIGHT, myABS(correctionAngle));   
				}			
				else
				{
					Motor_If_Forward(RIGHT, 1);
					Motor_If_Forward(LEFT, 0);

					Motor_Set_Speed(LEFT, myABS(correctionAngle)); 
					Motor_Set_Speed(RIGHT, myABS(correctionAngle));    
				}
				// update the current angle
				for(;i < 30;i++)
				{
						temp = Inertia_Get_Angle_Yaw();
						if (max < temp)
								max = temp;
						if (min > temp)
								min = temp;
						angleNow += temp;
				}
				angleNow = (angleNow - max - min)/28;
		}
		Motor_Set_Speed(LEFT, 0); 
		Motor_Set_Speed(RIGHT, 0);    
	
		// after the turning, we should set the speed for the straight line
		// but this function only set the parameter of the PID function
		// use a global parameter
		//Motor_If_Forward(RIGHT, 1);
		//Motor_If_Forward(LEFT, 1);
		//currentSettedSpeed = speed;
}

/*
* we know the current position and we know the target position, so we need
* turn an approprite angle and go straight to reach the target position.
* When we go straight, we should know how far we have ran.
*/
void goToPosition(int16_t currentX, int16_t currentY, int16_t targetX, int16_t targetY)
{
	// get the distance
	int16_t straightDistance = sqrt(pow(targetY-currentY, 2) + pow(targetX-currentX, 2));
	
	// we should calculate the angle we should turn
	// int16_t currentAngle = Inertia_Get_Angle_Yaw();
	int16_t turnAngle = asin(myABS((targetY-currentY)/straightDistance));

	// turn the angle and set the speed 
	if(targetX > currentX && targetY > currentY)          // first quadrant
		Motor_Move(turnAngle, 1, MAX_SPEED);
	else if(targetX < currentX && targetY > currentY)   // second quadrant
		Motor_Move(-turnAngle, 1, MAX_SPEED);
	else if(targetX < currentX && targetY < currentY)   // third quadrant
		Motor_Move(turnAngle - MAX_ANGLE/2, 1, MAX_SPEED);
	else                                                                  // forth quadrant
		Motor_Move(MAX_ANGLE/2 - turnAngle, 1, MAX_SPEED);

	// run the distance
	// TODO
}
