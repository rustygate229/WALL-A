#include "line_follow.h"

//initialize analog sensors
AnalogInputPin middle_op(FEHIO::P1_3);

bool checkOnLine() {
    float middleValue = middle_op.Value();

    if (middleValue <= 2.35) {
        return true;
    } else {
        return false;
    }
}
