#include "PID.h"

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
    //p
    this->Kp = Kp;
    //i == should be small
    this->Ki = Ki;
    //d
    this->Kd = Kd;

    d_error = 0.0;
    p_error = 0.0;
    i_error = 0.0;
}

void PID::UpdateError(double cte) {
    d_error = cte - p_error;
    p_error = cte;
    i_error = i_error + cte;
}

double PID::TotalError() {
    double err = (-Kp * p_error -Kd * d_error - Ki * i_error);
    if(err > 1.0 ) err = 1.0 ;
    else if(err < -1.0 ) err = -1.0;
    return err ;
}

