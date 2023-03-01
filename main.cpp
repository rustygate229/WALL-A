#include <FEHLCD.h>
#include <FEHMotor.h>
#include <FEHIO.h>

#define RADIUS 1.75
#define LEFT_MOTORSPEED -27.0
#define RIGHT_MOTORSPEED 25.0
#define RAMP_LEFT -37.0
#define RAMP_RIGHT 35.0
#define PI 3.1415927

//Declarations for encoders & motors
DigitalEncoder right_encoder(FEHIO::P2_6);
DigitalEncoder left_encoder(FEHIO::P2_7);
FEHMotor right_motor(FEHMotor::Motor0, 9.0);
FEHMotor left_motor(FEHMotor::Motor1, 9.0);

void move(int a, float distance);
void ramp(int a, float distance);
void rotate(int direction, float angle);
bool detectLight(AnalogInputPin a);

int main(void)
{
    rotate(1, 48.0);
    move(-1, 14);
    ramp(-1, 18);
    move(-1, 3);
    rotate(-1, 45.0);
    move(-1, 13);
    rotate(1, 45.0);
    move(-1, 12);
}

bool detectLight(AnalogInputPin cds) {

    // checks if light is on
    if (cds.Value() < 2.0) {
        return true;
    }

    return false;

}

void move(int direction, float distance) {

    //Calculate # of counts
    int counts = (distance * 318) / (2 * PI * RADIUS);

    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    //Set both motors to desired percent
    right_motor.SetPercent(direction * RIGHT_MOTORSPEED);
    left_motor.SetPercent(direction * LEFT_MOTORSPEED);
    
    while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts);

    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}

void ramp(int direction, float distance) {

    //Calculate # of counts
    int counts = (distance * 318) / (2 * PI * RADIUS);

    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    //Set both motors to desired percent
    right_motor.SetPercent(direction * RAMP_RIGHT);
    left_motor.SetPercent(direction * RAMP_LEFT);
    
    while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts);

    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}

void rotate(int direction, float angle) {
    //Calculate # of counts
    int counts = 180 * (angle / 90);
    
    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    //Set both motors to desired percent
    //hint: set right motor backwards, left motor forwards
    right_motor.SetPercent(direction * -RIGHT_MOTORSPEED);
    left_motor.SetPercent(direction * LEFT_MOTORSPEED);

    //While the average of the left and right encoder is less than counts,
    //keep running motors
    while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts);
    
    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();

}
