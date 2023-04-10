#include <FEHIO.h>
#include <FEHMotor.h>
#include <FEHUtility.h>

#define PI 3.1415927
#define RADIUS 1.75
#define LEFT_MOTORSPEED -26.0
#define RIGHT_MOTORSPEED 28.0
#define RAMP_LEFT -37.0
#define RAMP_RIGHT 39.0

extern FEHMotor right_motor;
extern FEHMotor left_motor;
extern DigitalInputPin left_bump;
extern DigitalInputPin right_bump;

void move(float a, float distance);
void ramp(int a, float distance);
void rotate(int direction, float angle);
void hit_bump(float angle);