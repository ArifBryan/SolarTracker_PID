#define SENSOR1_PIN A0
#define SENSOR2_PIN A1
#define SENSOR3_PIN A2
#define SENSOR4_PIN A3

#define SENSOR_SAMPLE_INTERVAL  100
#define SENSOR_FILTER_KF        8

uint32_t sensorTimer;
int16_t sensorRawData[4];
int16_t sensorData[4];
uint16_t sensorAvg;

const uint16_t sensorOffset[4] = {0, 0, 0, 0};

void Sensor_Init(){
  pinMode(SENSOR1_PIN, INPUT);
  pinMode(SENSOR2_PIN, INPUT);
  pinMode(SENSOR3_PIN, INPUT);
  pinMode(SENSOR4_PIN, INPUT);
}

void Sensor_Handler(){
  if(millis() - sensorTimer >= SENSOR_SAMPLE_INTERVAL){
    sensorRawData[0] = analogRead(SENSOR1_PIN) - sensorOffset[0];
    sensorRawData[1] = analogRead(SENSOR2_PIN) - sensorOffset[1];
    sensorRawData[2] = analogRead(SENSOR3_PIN) - sensorOffset[2];
    sensorRawData[3] = analogRead(SENSOR4_PIN) - sensorOffset[3];
    for(uint8_t i = 0; i < 4; i++){
      sensorData[i] = (sensorRawData[i] + (sensorData[i] * SENSOR_FILTER_KF)) / (SENSOR_FILTER_KF + 1);
    }
    sensorAvg = (sensorData[0] + sensorData[1] + sensorData[2] + sensorData[3]) / 4;
    
    sensorTimer = millis();
  }
}

int16_t Sensor_GetAvg(){
  return sensorAvg;
}

int16_t Sensor_GetXpos(){
  uint16_t avg1, avg2;

  avg1 = (sensorData[0] + sensorData[1]) / 2;
  avg2 = (sensorData[2] + sensorData[3]) / 2;
  
  return avg1 - avg2;
}

int16_t Sensor_GetYpos(){
  uint16_t avg1, avg2;

  avg1 = (sensorData[0] + sensorData[3]) / 2;
  avg2 = (sensorData[1] + sensorData[2]) / 2;
  
  return avg2 - avg1;
}

int16_t Sensor1_GetData(){
  return sensorData[0];
}
int16_t Sensor2_GetData(){
  return sensorData[1];
}
int16_t Sensor3_GetData(){
  return sensorData[2];
}
int16_t Sensor4_GetData(){
  return sensorData[3];
}
