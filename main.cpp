#include <FEHLCD.h>
#include <FEHMotor.h>
#include <FEHIO.h>
#include <FEHUtility.h>

#define RADIUS 1.75
#define LEFT_MOTORSPEED -28.0
#define RIGHT_MOTORSPEED 26.0
#define RAMP_LEFT -35.0
#define RAMP_RIGHT 35.0
#define PI 3.1415927

//Declarations for encoders & motors
DigitalEncoder right_encoder(FEHIO::P2_6);
DigitalEncoder left_encoder(FEHIO::P2_7);
FEHMotor right_motor(FEHMotor::Motor0, 9.0);
FEHMotor left_motor(FEHMotor::Motor1, 9.0);

void move(float a, float distance);
void ramp(int a, float distance);
void rotate(int direction, float angle);
bool detectLight(AnalogInputPin a);
int kioskLight(AnalogInputPin);

int main(void)
{
    AnalogInputPin cdsCell(FEHIO::P1_0);

    while (!detectLight(cdsCell));

    // gets to plane
    
    rotate(1, 65.0); // initial rotation
    Sleep(0.5);
    move(-1, 10); // move closer to ramp
    Sleep(0.5);
    rotate(-1, 17.0); // correction rotation
    Sleep(0.5);
    ramp(-1, 22); // goes up the ramp
    Sleep(0.5);

    
    move(-1, 2); // moves 2 inches from the ramp
    Sleep(0.5);
    rotate(1, 90); // rotates clockwise 90 degrees
    Sleep(0.5);
    move(-1, 7); // lines back up with wall
    Sleep(0.5);
    move(1, 22); // moves forward 22 inches

    // robot at middle of airplane

    //gets to light
    rotate(1, 80); // rotates to light
    
    // moves 1 inch at a time until it detects light
    do {
        move(1, 1);
    } while (!detectLight(cdsCell));

    float time = TimeNow();
    int color = 0;

    // detects light for 2 seconds
    while (TimeNow() - time < 2) {
        color = kioskLight(cdsCell);
    }

    // moves back for clearance
    move(-1, 3);
    rotate(-1, 85); // rotates to travel to button
    
    // if the light is blue
    if (color == 1) {
        move(-1, 5); 
    // if light is red
    } else if (color == 2) {
        move(-1, 10.5);
    }

    // rotate and crash into button
    rotate(-1, 78);
    move(-1, 10);

    // move back down the ramp
    move(1, 14);
    rotate(1, 80);
    move(-1, 18);
    move(1, 3);
    rotate(1, 80);
    move(-1, 15);
}

bool detectLight(AnalogInputPin cds) {

    // checks if light is on
    if (cds.Value() < 1) {
        return true;
    }

    return false;

}

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
    //hint: set right motor backwards, left motor forwards
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

int kioskLight(AnalogInputPin cds) {

    LCD.Clear();
    float cdsValue = cds.Value();

    // if cds cell detects light
    if (cdsValue < 1.5) {
        // if light is blue
        if (cdsValue > 0.4) {
            LCD.SetBackgroundColor(BLUE);
            return 1;
        // if light is red
        } else {
            LCD.SetBackgroundColor(RED);
            return 2;
        }
    
    // cell does not detect light
    } else {
        LCD.SetBackgroundColor(BLACK);
        LCD.WriteLine("Do not detect light");
        return 0;
    }
}