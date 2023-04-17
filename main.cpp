#include <FEHServo.h>

#include "robot_movement.h"
#include "corrections.h"
#include "light_checks.h"
#include "line_follow.h"

// gets robot to luggage station and drops luggage
void LuggageTask(FEHServo);

//gets robot to passport station and stamps passport
void passportTask(FEHServo);

// gets to light and returns the color
// 1:Blue, 2:Red, 1: No light is detected (defaults to blue)
int getToLight(AnalogInputPin);

// get to appropriate button
void getToButton(int);

// gets to Fuel Lever and flips it
void getToFuelLever(FEHServo);

// Presses red button to finish run
void finishRun();

int main(void)
{
    /* Initializiation Actions */
    FEHServo pass_servo(FEHServo::Servo3);
    FEHServo fuel_servo(FEHServo::Servo0);

    // Set Min and Max of servos
    pass_servo.SetMin(500);
    pass_servo.SetMax(2379);

    fuel_servo.SetMin(500);
    fuel_servo.SetMax(2500);

    RPS.InitializeTouchMenu();
    
    // Wait until start light is detected
    while (!detectLight());

    // Set servos to starting positions
    fuel_servo.SetDegree(160);
    pass_servo.SetDegree(60);

    LuggageTask(pass_servo);
    passportTask(pass_servo);

    int button = getToLight(cdsCell);

    LCD.WriteLine(button);

    getToButton(button);

    getToFuelLever(fuel_servo);

    finishRun();
}

void LuggageTask(FEHServo pass_servo) {
    /* Get to luggage */
    rotate(1, 68.0); // initial rotation
    Sleep(0.2);
    move(-1, 10.5); // move closer to ramp
    Sleep(0.2);
    pulse_x(28.5,-1);
    rotate(-1, 18);
    //check_heading(0); // correction rotation
    Sleep(0.2);
    ramp(-1, 22); // goes up the ramp
    Sleep(0.2);
    rotate(-1, 85.0);
    Sleep(0.2);

    move(1, 1);
    hit_bump();

    Sleep(.2);
    move(-1,14);

    /* Drop the luggage */
    pass_servo.SetDegree(160);
    Sleep(0.5);
    pass_servo.SetDegree(30);
}

void passportTask(FEHServo pass_servo) {

    // Move forward and rotate
    move(1, 2.5);
    rotate(-1, 76);

    // Put arm down
    pass_servo.SetDegree(170);

    // Move forward until robot reaches lever
    move(1, 8);

    Sleep(0.1);

    pass_servo.SetDegree(100);
    move(1,3);
    rotate(1, 3);
    pass_servo.SetDegree(85);

    //rotate(1, 2);

    move(1, 3.5);

    // lower lever
    pass_servo.SetDegree(10);
    move(1, 2);
    pass_servo.SetDegree(85);
    move(-1, 7);

    pass_servo.SetDegree(60);
}

int getToLight(AnalogInputPin cdsCell) {

    rotate(-1, 87);

    move(1, 15);
    hit_bump();

    move(-1, 5.5);
    rotate(-1, 87);

    while (!detectLight()) {
        move(-1, 1);
    }

    Sleep(1.0);

    return kioskLight();

}

void getToButton(int color) {
    move(1, 5);
    rotate(1, 83);

    // if the light is blue
    if (color == 1) {
        move(-1, 5); 
    // if light is red
    } else if (color == 2) {
        move(-1, 10.5);
    }

    rotate(-1, 80);

    buttonHit(-1, 10);
}

void getToFuelLever(FEHServo arm_servo) {

    int lever = RPS.GetCorrectLever();

    move(1, 16);
    rotate(1, 94);
    move(1, 10);
    hit_bump();
    move(-1, 1);
    rotate(-1, 83);
    move(1, 24);
    pulse_y(23.1, -1);
    rotate(1, 90);
    move(1, 1);
    hit_bump();

    LCD.WriteLine(RPS.Y());

    switch (lever)
    {
    case 0:
        move(-1, 9);
        break;
    case 1:
        move(-1, 4);
        break;
    case 2:
        move(-1, 1);
        break;

    default:
        // Something is very wrong
        break;
    }

    rotate(-1, 80);
    move(1, 2.75);
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

    Sleep(0.5);
    arm_servo.SetDegree(35);
    move(-1, 2);
    arm_servo.SetDegree(160);

}

void finishRun() {

    rotate(1, 85);
    buttonHit(1, 10);
    move(-1, 10);
    rotate(1, 38);
    move(-1, 25);

}