#include "PID.h"

void PID_TypeDef::SetLimit(float mn, float mx){
  this->mn = mn;
  this->mx = mx;
}

void PID_TypeDef::SetConstants(float kp, float ki, float kd, float ts){
  this->kp = kp;
  this->ki = ki;
  this->kd = kd;
  this->ts = ts;
  Reset();
}

void PID_TypeDef::Calculate(float sp, float av){
  e = sp - av;
  if(millis() - timer >= ts * 1000){
    de = e - le;
    if((u >= mx && e < 0)&& (u <= mn && e > 0)){
      se += e;
    }
    else if(u > mn && u < mx){
      se += e;
    }

    timer = millis();
  }
  u = (kp * e) + (ki * se) + (kd * de);
  u = (u < mn ? mn : (u > mx ? mx : u));
}

void PID_TypeDef::Reset(){
  u = 0;
  le = 0;
  de = 0;
  se = 0;
  e = 0;
}

float PID_TypeDef::GetError(){
  return e;
}

float PID_TypeDef::GetResult(){
  return u;
}
