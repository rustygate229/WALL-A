#include <FEHRPS.h>
#include <FEHLCD.h>
#include "robot_movement.h"

void pulse_x(float x_coordinate, int orientation);
void pulse_y(float x_coordinate, int orientation);
void check_heading(float heading);
void hit_bump();