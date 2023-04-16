#include "robot_movement.h"

//Declarations for encoders & motors
DigitalEncoder right_encoder(FEHIO::P2_6);
DigitalEncoder left_encoder(FEHIO::P2_7);
FEHMotor right_motor(FEHMotor::Motor0, 9.0);
FEHMotor left_motor(FEHMotor::Motor1, 9.0);
DigitalInputPin right_bump(FEHIO::P1_7);
DigitalInputPin left_bump(FEHIO::P1_6);

void move(float direction, float distance) {

    //Calculate # of counts
    int counts = (distance * 318) / (2 * PI * RADIUS);

    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    //Set both motors to desired percent
    right_motor.SetPercent(direction * RIGHT_MOTORSPEED);
    left_motor.SetPercent(direction * LEFT_MOTORSPEED);
    
    float time = TimeNow();
    while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts)
    {
        if (TimeNow() - time > 6) {
            break;
        }
    }

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
    right_motor.SetPercent(direction * -RIGHT_MOTORSPEED);
    left_motor.SetPercent(direction * LEFT_MOTORSPEED);

    //While the average of the left and right encoder is less than counts,
    //keep running motors
    float time = TimeNow();

    while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts) {
        if (TimeNow() - time > 6) {
            break;
        }
    }
    
    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();

}

void buttonHit(float direction, float distance) {

    //Calculate # of counts
    int counts = (distance * 318) / (2 * PI * RADIUS);

    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    //Set both motors to desired percent
    right_motor.SetPercent(direction * RIGHT_MOTORSPEED);
    left_motor.SetPercent(direction * LEFT_MOTORSPEED);
    
    float time = TimeNow();
    while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts)
    {
        if (TimeNow() - time > 2.5) {
            break;
        }
    }

    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}