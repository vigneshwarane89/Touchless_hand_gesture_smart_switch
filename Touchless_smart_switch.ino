#include "Adafruit_APDS9960.h"
Adafruit_APDS9960 apds;

int isr_flag = 0;
int proximity_data = -1;
void interruptRoutine() {
  isr_flag = 1;
}
void setup() {
  Serial.begin(115200);
  pinMode(3,OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  attachInterrupt(0, interruptRoutine, FALLING);
  
  if(!apds.begin()){
    Serial.println("failed to initialize device! Please check your wiring.");
  }
  else Serial.println("Device initialized!");
  apds.enableGesture(true);
}

void loop() {
    uint8_t gesture = apds.readGesture();
    switch(gesture){
      case APDS9960_LEFT:
        Serial.println("Switch ON");
        digitalWrite(LED_BUILTIN,HIGH);
        apds.enableProximity(true);
        if ( isr_flag == 1 ){
         
          if ( !apds.readProximity() ) {
                Serial.println("Error reading proximity value");
          } else {
                analogWrite(9,proximity_data);
                digitalWrite(2,HIGH);
                digitalWrite(2,LOW);
                if(proximity_data >=255){      
                  Serial.println("Speed : Fast");        
                }
                else if(proximity_data >=150 and proximity_data<=240){
                  Serial.println("Speed : Medium"); 
                }
                else if(proximity_data >=0 and proximity_data<=130){
                  Serial.println("Speed : Slow"); 
                }
                break;
                
        case APDS9960_RIGHT:
          Serial.println("Switch OFF");
          digitalWrite(LED_BUILTIN,LOW);
          apds.enableProximity(false);
          break;
          isr_flag = 0;
      }
      isr_flag = 0;
   }
  }     
}
