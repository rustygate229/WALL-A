#include "line_follow.h"

//initialize analog sensors
AnalogInputPin left_op(FEHIO::P1_0);
AnalogInputPin middle_op(FEHIO::P1_3);
AnalogInputPin right_op(FEHIO::P1_7);

bool checkOnLine(float value) {
    float leftValue = left_op.Value();
    float middleValue = middle_op.Value();
    float rightValue = right_op.Value();

    float average = (leftValue + middleValue + rightValue) / 3;

    if (average <= value) {
        return true;
    } else {
        return false;
    }
}
