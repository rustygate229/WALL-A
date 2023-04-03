#include <FEHIO.h>
#include <FEHMotor.h>
#include <FEHUtility.h>

#define PI 3.1415927
#define RADIUS 1.75
#define LEFT_MOTORSPEED -28.0
#define RIGHT_MOTORSPEED 25.0
#define RAMP_LEFT -35.0
#define RAMP_RIGHT 35.0

extern FEHMotor right_motor;
extern FEHMotor left_motor;

void move(float a, float distance);
void ramp(int a, float distance);
void rotate(int direction, float angle);