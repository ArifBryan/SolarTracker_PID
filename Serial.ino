#define SERIAL_TX_INTERVAL  250

uint32_t serialTimer;

void Serial_Init(){
  Serial.begin(115200);
}

void Serial_Handler(){
  if(millis() - serialTimer >= SERIAL_TX_INTERVAL){
//    Serial.print(Sensor1_GetData());
//    Serial.print(",");
//    Serial.print(Sensor2_GetData());
//    Serial.print(",");
//    Serial.print(Sensor3_GetData());
//    Serial.print(",");
//    Serial.print(Sensor4_GetData());
//    Serial.println("");
    
//    Serial.print(Stepper1_GetPos());
//    Serial.print(",");
//    Serial.print(Stepper2_GetPos());
//    Serial.println("");

    Serial.print(PID1.GetError());
    Serial.print(",");
    Serial.print(PID2.GetError());
    Serial.println("");
    
    serialTimer = millis();
  }
}
