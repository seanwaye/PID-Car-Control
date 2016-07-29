/***************************************************************************************
*
*  Used functions:
*  Motor_If_Forward(left_or_right, if_forward)       decide the direction of the motor
*  Motor_Set_Speed(left_or_right, speed)             set the speed
*  Inertia_Get_Angle_Yaw()  get the angle from the gyroscope(double)
*  Get_Speed(left_or_right) get speed number (0 ~ 1000) 
*  
*  Output function:
*  Moter_Move(uint16_t angle, bool if_related, uint16_t speed)
*  	parameters:                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
*      angle: the angle that want to move
*      if_related: 1 means relative angle to current angle
*                  0 means absolutely angle
*      speed: the speed of the motor after turning
*
*  The angle we get from the gyroscope is from -180 to 180, but in order to simplify the
*  adjustion, we convert the scope from 0 to 360, clockwise represents turning right
*
****************************************************************************************/
#ifndef MOTOR_CONTROL
#define MOTOR_CONTROL

#include "stm32f10x.h"

// some constrain
#define MAX_SPEED 1000   
#define MAX_ANGLE 360
#define MIN_ANGLE 0
#define LEFT 0
#define RIGHT 1

// PID parameters (angle)
#define P_DATA_ANGLE 5
#define I_DATA_ANGLE 5
#define D_DATA_ANGLE 0
#define ACCEPTTED_ERROR_ANGLE 3

// PID parameters (speed)
#define P_DATA_SPEED 5
#define I_DATA_SPEED 0
#define D_DATA_SPEED 0

/************************  useful tools  ******************************/

// constrain the angle and speed
int16_t constrain(int16_t input, int16_t min, int16_t max);
// contrain2 form -180 to 180
int16_t constrain2(int16_t input);
// transform the abgle from 180 to 360  
int16_t angleTransform(int16_t angle_ABS180);
// get absolutely value
int16_t myABS(int16_t value);
int16_t calculateAngleDifference(int16_t angle1, int16_t angle2);

/**********************************************************************/

// go to the target position
void goToPosition(int16_t currentX, int16_t currentY, int16_t targetX, int16_t targetY, int16_t speed);

#endif // MOTOR_CONTROL
