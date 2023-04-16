#include "corrections.h"

void pulse_x(float x_coordinate, int orientation){
    // Determine the direction of the motors based on the orientation of the QR code
    int power = 1;
    if (orientation == -1)
    {
        power = -1;
        
    }

    LCD.WriteLine(RPS.X());

    // Check if receiving proper RPS coordinates and whether the robot is within an acceptable range
    while ((RPS.X() != -1) && (RPS.X() < x_coordinate - 0.5 || RPS.X() > x_coordinate + 0.5))
    {

        LCD.WriteLine(RPS.X());
        if (RPS.X() > x_coordinate + 0.5)
        {
            // Pulse the motors for a short duration in the correct direction
            move(-power, .5);
        }
        else if (RPS.X() < x_coordinate - 0.5)
        {
            // Pulse the motors for a short duration in the correct direction
            move(power, .5);
        }
        
        Sleep(.35);
    }
}

void pulse_y(float y_coordinate, int orientation){
    // Determine the direction of the motors based on the orientation of the QR code
    int power = 1;
    if (orientation == -1)
    {
        power = -1;
        
    }

    LCD.WriteLine(RPS.Y());

    // Check if receiving proper RPS coordinates and whether the robot is within an acceptable range
    while ((RPS.Y() != -1) && (RPS.Y() < y_coordinate - 0.5 || RPS.Y() > y_coordinate + 0.5))
    {

        LCD.WriteLine(RPS.Y());
        if (RPS.Y() > y_coordinate + 0.5)
        {
            // Pulse the motors for a short duration in the correct direction
            move(-power, .5);
        }
        else if (RPS.Y() < y_coordinate - 0.5)
        {
            // Pulse the motors for a short duration in the correct direction
            move(power, .5);
        }
        
        Sleep(.35);
    }
}

void check_heading(float heading)
{

    int dir = 1;
    
    // Check if receiving proper RPS coordinates and whether the robot is within an acceptable range
    while ((RPS.Y() != -1) && (RPS.Heading() < heading - 2 || RPS.Heading() > heading + 2))
    {
        LCD.WriteLine(RPS.Heading());
        if (RPS.Heading() < heading - 2)
        {
            dir = -1;
        }
        else if (RPS.Heading() > heading + 2)
        {
            dir = 1;
        }

        if (heading - RPS.Heading() >=  180){
            dir=1;
        }
        if(RPS.Heading()-heading >= 180){
            dir=-1;
        }
        rotate(dir, 4);
        Sleep(.35);
    }
}

void hit_bump() {

    // Drive
    right_motor.SetPercent(RIGHT_MOTORSPEED);
    left_motor.SetPercent(LEFT_MOTORSPEED);
    
    float time = TimeNow();
    while ((left_bump.Value() || right_bump.Value()) && (TimeNow() - time < 2));

    right_motor.Stop();
    left_motor.Stop();
}