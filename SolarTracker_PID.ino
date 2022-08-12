#include "PID.h"

#define STEPPER1_LIMIT_MIN  -350
#define STEPPER1_LIMIT_MAX  350
#define STEPPER2_LIMIT_MIN  -500
#define STEPPER2_LIMIT_MAX  500

#define POSITION_TOLERANCE  5

PID_TypeDef PID1, PID2;

void setup() {
  Serial_Init();
  Sensor_Init();
  Stepper_Init();
  // Konstanta PID : (Kp, Ki, Kd, Ts)
  // PID1 : Tilt
  PID1.SetConstants(0.1, 0.03, 0, 0.1);
  PID1.SetLimit(STEPPER1_LIMIT_MIN, STEPPER1_LIMIT_MAX);
  // PID2 : Yaw
  PID2.SetConstants(0.1, 0.03, 0, 0.1);
  PID2.SetLimit(STEPPER2_LIMIT_MIN, STEPPER2_LIMIT_MAX);
}

void loop() {
  Sensor_Handler();

  // Jika rata-rata sensor cahaya > 10
  if(Sensor_GetAvg() > 10){
    // Kontrol PID tilt
    PID1.Calculate(0, Sensor_GetXpos());
    if(abs(PID1.GetResult() - Stepper1_GetPos()) > POSITION_TOLERANCE){
      // Stepper tilt
      Stepper1_SetPos(PID1.GetResult());
    }

    // Kontrol PID yaw
    if(Stepper1_GetPos() < 0){
      PID2.Calculate(0, Sensor_GetYpos());
    }
    else{
      PID2.Calculate(0, -Sensor_GetYpos());
    }
    if(abs(PID2.GetResult() - Stepper2_GetPos()) > POSITION_TOLERANCE){
      // Stepper yaw
      Stepper2_SetPos(PID2.GetResult());
    }
  }
  else{
    PID1.Reset();
    PID2.Reset();
    Stepper1_SetPos(0);
    Stepper2_SetPos(0);
  }
  
  Stepper_Handler();
  Serial_Handler();
}
