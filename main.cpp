#include <FEHLCD.h>
#include <FEHMotor.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHServo.h>
#include <FEHRPS.h>

#define RADIUS 1.75
#define LEFT_MOTORSPEED -28.0
#define RIGHT_MOTORSPEED 25.0
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
void lineFollowFuel();

int main(void)
{
    RPS.InitializeTouchMenu();
    
    AnalogInputPin cdsCell(FEHIO::P0_5);
    FEHServo arm_servo(FEHServo::Servo0);

    arm_servo.SetMin(500);
    arm_servo.SetMax(2500);

    while (!detectLight(cdsCell));

    arm_servo.SetDegree(180);

    move(-1,16);
    Sleep(0.5);
    rotate(-1,33);
    Sleep(0.5);
    move(-1,15);
    Sleep(0.5);

    int lever = RPS.GetCorrectLever();

    LCD.Clear();
    LCD.SetBackgroundColor(BLACK);
    LCD.WriteLine(lever);

    switch (lever)
    {
    case 0:
        move(1,12);
        break;
    case 1:
        move(1, 9);
        break;
    case 2:
        move(1, 4);
        break;

    default:
        // Something is very wrong
        break;
    }


    Sleep(0.5);
    rotate(1,85);
    Sleep(0.5);
    move(1, 1);

    Sleep(0.5);

    arm_servo.SetDegree(90);

    Sleep(0.5);

    arm_servo.SetDegree(180);

    Sleep(0.5);

    move(-1, 3);

    Sleep(5.0);

    arm_servo.SetDegree(30);

    Sleep(0.5);

    move(1, 3);

    Sleep(0.5);

    arm_servo.SetDegree(90);

    
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

// line follow code
void lineFollowFuel() {
    //initialize analog sensors
    AnalogInputPin left_op(FEHIO::P1_0);
    AnalogInputPin middle_op(FEHIO::P1_3);
    AnalogInputPin right_op(FEHIO::P1_7);

    // all possible line states
    enum LINESTATES {
        MIDDLE,
        RIGHT,
        LEFT,
        RIGHTTURN,
        LEFTTURN,
        OFF
    };

    int state = MIDDLE; // Set the initial state

    while (state != OFF) { // I will follow this line forever!

        switch(state) {

            // If I am in the middle of the line...

            case MIDDLE:

                // Set motor powers for driving straight
                right_motor.SetPercent(RIGHT_MOTORSPEED);
                left_motor.SetPercent(LEFT_MOTORSPEED);

                /* Drive */

                if (right_op.Value() < 2.4) {

                    state = RIGHT; // update a new state

                }

                /* Code for if left sensor is on the line */
                if (left_op.Value() < 2.6) {
                    state = LEFT;
                }


                break;

            // If the right sensor is on the line...
            case RIGHT:

                // Set motor powers for right turn
                right_motor.SetPercent(25);
                left_motor.SetPercent(-12);

                /* Drive */

                if(middle_op.Value() <= 2.35) {

                    state = MIDDLE;

                }

                break;

            // If the left sensor is on the line...
            case LEFT:

                // Set motor powers for right turn
                right_motor.SetPercent(12);
                left_motor.SetPercent(-25);

                /* Drive */

                if(middle_op.Value() <= 2.35) {

                    state = MIDDLE;

                }

                break;

            default: // Error. Something is very wrong.

                break;

        }

        // Sleep a bit
        Sleep(50);

    }

}
