#include <FEHServo.h>

#include "robot_movement.h"
#include "light_checks.h"
#include "line_follow.h"

int main(void)
{
    FEHServo pass_servo(FEHServo::Servo3);

    pass_servo.SetMin(500);
    pass_servo.SetMax(2379);

    while (!detectLight());

    pass_servo.SetDegree(10);

    rotate(1, 65.0); // initial rotation
    Sleep(0.5);
    move(-1, 10); // move closer to ramp
    Sleep(0.5);
    rotate(-1, 17.0); // correction rotation
    Sleep(0.5);
    ramp(-1, 23); // goes up the ramp
    Sleep(0.5);
    rotate(1, 85.0);
    Sleep(0.5);
    move(-1, 9);
    Sleep(0.5);
    move(1, 12);

    Sleep(0.5);
    rotate(1, 77);
    Sleep(0.5);
    pass_servo.SetDegree(180);
    move(1, 6);
    Sleep(0.25);
    pass_servo.SetDegree(110);
    move(1, 3);
    Sleep(0.25);
    pass_servo.SetDegree(85);
    move(1, 2.5);

    // lower lever
    pass_servo.SetDegree(10);
    move(1, 2);
    pass_servo.SetDegree(85);
    move(-1, 6);
}