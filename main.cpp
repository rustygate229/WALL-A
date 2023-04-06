#include <FEHServo.h>

#include "robot_movement.h"
#include "rps_functions.h"
#include "light_checks.h"
#include "line_follow.h"

int main(void)
{
    FEHServo pass_servo(FEHServo::Servo3);
    AnalogInputPin cdsCell(FEHIO::P0_5);

    pass_servo.SetMin(500);
    pass_servo.SetMax(2379);

    RPS.InitializeTouchMenu();
    
    while (!detectLight());

    pass_servo.SetDegree(60);
    

    rotate(1, 65.0); // initial rotation
    Sleep(0.5);
    move(-1, 10); // move closer to ramp
    Sleep(0.5);
    pulse_x(29,-1);
    rotate(-1, 22.0); // correction rotation
    Sleep(0.5);
    ramp(-1, 22.5); // goes up the ramp
    Sleep(0.5);
    rotate(-1, 85.0);
    Sleep(0.5);
    move(1, 9);
    Sleep(.5);
    move(-1,14);
    pass_servo.SetDegree(160);
    Sleep(1.0);
    pass_servo.SetDegree(30);
    move(1,3);
    Sleep(0.5);
    rotate(1,4);
    Sleep(0.5);
    move(-1,22);
    Sleep(0.5);
    move(1, 4);
    Sleep(0.5);
    rotate(1,90);
    Sleep(0.5);
    move(1,22); // move down the ramp

    Sleep(0.5);
    rotate(1, 90);
    Sleep(0.5);
    move(1, 5);
    Sleep(.5);
    move(-1,12);
    Sleep(0.5);
    rotate(1, 40);
    Sleep(0.5);
    move(-1, 22);
}
