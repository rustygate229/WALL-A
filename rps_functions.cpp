#include "rps_functions.h"

void pulse_x(float x_coordinate, int orientation){
    // Determine the direction of the motors based on the orientation of the QR code
    int power = 1;
    if (orientation == -1)
    {
        power = -1;
        
    }

    LCD.WriteLine(RPS.X());

    int count = 0; 

    // Check if receiving proper RPS coordinates and whether the robot is within an acceptable range
    while ((RPS.X() != -1) && (RPS.X() < x_coordinate - 0.5 || RPS.X() > x_coordinate + 0.5))
    {
        if (count > 15) {
            break;
        }

        if (RPS.X() > x_coordinate + 1)
        {
            // Pulse the motors for a short duration in the correct direction
            move(-power, .5);
        }
        else if (RPS.X() < x_coordinate - 1)
        {
            // Pulse the motors for a short duration in the correct direction
            move(power, .5);
        }
        
        Sleep(.35);
        count++;
    }
}