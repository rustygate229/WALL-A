#include <FEHServo.h>

#include "robot_movement.h"
#include "rps_functions.h"
#include "light_checks.h"
#include "line_follow.h"

int main(void)
{
    /* Initializiation Actions */
    FEHServo pass_servo(FEHServo::Servo3);
    FEHServo fuel_servo(FEHServo::Servo7);
    AnalogInputPin cdsCell(FEHIO::P0_5);

    pass_servo.SetMin(500);
    pass_servo.SetMax(2379);

    fuel_servo.SetMin(500);
    fuel_servo.SetMax(2500);

    RPS.InitializeTouchMenu();
    
    // Start light
    while (!detectLight());

    pass_servo.SetDegree(60);

    /* Get to luggage */
    rotate(1, 65.0); // initial rotation
    Sleep(0.5);
    move(-1, 10); // move closer to ramp
    Sleep(0.5);
    pulse_x(29,-1);
    rotate(-1, 14);
    check_heading(0); // correction rotation
    Sleep(0.5);
    ramp(-1, 22.5); // goes up the ramp
    Sleep(0.5);
    rotate(-1, 85.0);
    Sleep(0.5);

    move(1, 1);
    hit_bump(90);

    Sleep(.5);
    move(-1,14);

    /* Drop the luggage */
    pass_servo.SetDegree(160);
    Sleep(1.0);
    pass_servo.SetDegree(30);
    move(1,3);

}
