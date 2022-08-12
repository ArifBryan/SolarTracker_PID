#define STEPPER1_PUL_PIN  8
#define STEPPER1_DIR_PIN  9
#define STEPPER2_PUL_PIN  10
#define STEPPER2_DIR_PIN  11

#define STEPPER_PULSE_INTERVAL  20

int32_t stepper1PulseNow;
int32_t stepper1PulseSet;
int32_t stepper2PulseNow;
int32_t stepper2PulseSet;
int32_t stepperTimer;

void Stepper_Init(){
  pinMode(STEPPER1_PUL_PIN, OUTPUT);
  pinMode(STEPPER1_DIR_PIN, OUTPUT);
  pinMode(STEPPER2_PUL_PIN, OUTPUT);
  pinMode(STEPPER2_DIR_PIN, OUTPUT);
}

void Stepper_Handler(){
  if(millis() - stepperTimer >= STEPPER_PULSE_INTERVAL){
    if(stepper1PulseSet > stepper1PulseNow){
      digitalWrite(STEPPER1_DIR_PIN, HIGH);
      digitalWrite(STEPPER1_PUL_PIN, HIGH);
      digitalWrite(STEPPER1_PUL_PIN, LOW);
      stepper1PulseNow++;
    }
    else if(stepper1PulseSet < stepper1PulseNow){
      digitalWrite(STEPPER1_DIR_PIN, LOW);
      digitalWrite(STEPPER1_PUL_PIN, HIGH);
      digitalWrite(STEPPER1_PUL_PIN, LOW);
      stepper1PulseNow--;
    }

    if(stepper2PulseSet > stepper2PulseNow){
      digitalWrite(STEPPER2_DIR_PIN, HIGH);
      digitalWrite(STEPPER2_PUL_PIN, HIGH);
      digitalWrite(STEPPER2_PUL_PIN, LOW);
      stepper2PulseNow++;
    }
    else if(stepper2PulseSet < stepper2PulseNow){
      digitalWrite(STEPPER2_DIR_PIN, LOW);
      digitalWrite(STEPPER2_PUL_PIN, HIGH);
      digitalWrite(STEPPER2_PUL_PIN, LOW);
      stepper2PulseNow--;
    }

    stepperTimer = millis();
  }
}

void Stepper1_SetPos(int32_t pos){
  stepper1PulseSet = pos;
}
void Stepper2_SetPos(int32_t pos){
  stepper2PulseSet = pos;
}

int32_t Stepper1_GetPos(){
  return stepper1PulseNow;
}
int32_t Stepper2_GetPos(){
  return stepper2PulseNow;
}
