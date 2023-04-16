#include "light_checks.h"

AnalogInputPin cdsCell(FEHIO::P0_5);

bool detectLight() {

    // checks if light is on
    if (cdsCell.Value() < 1) {
        return true;
    }

    return false;

}

int kioskLight() {

    LCD.Clear();
    float cdsValue = cdsCell.Value();
    LCD.WriteLine(cdsValue);
    
    // if cds cell detects light
    if (cdsValue < 1.5) {
        // if light is blue
        if (cdsValue > 0.6) {
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