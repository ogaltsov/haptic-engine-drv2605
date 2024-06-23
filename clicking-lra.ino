#include <Wire.h>
#include "Adafruit_DRV2605.h"

Adafruit_DRV2605 drv;

void setup() {
  Serial.begin(9600);
  Serial.println("Start");
  drv.begin();
    
  drv.useLRA();
  drv.setMode(DRV2605_MODE_REALTIME);
}

int from = 10;
int to = 23;
int indx = 10;

int T_action = 30;
int click_amp = 15;
int T_total = 1000;

void loop() {

  if (indx <= to ) {
  
    int N = indx;
    Serial.println(indx);

    int T_actions_total = T_action * N;
    int T_idle_total = T_total - T_actions_total;
    int T_idle = T_idle_total / N; 

    if(T_idle < 10) {
      Serial.println("worng interval");
      return;
    }

    for(uint8_t i = 0; i < 20; i++) {
      click();
      delay(T_idle);
    }  

    indx+=2;

  } else {

    delay(3000);
    indx = from;

  }
}

void click() {

  drv.setRealtimeValue(click_amp);
  delay(T_action);
  drv.setRealtimeValue(0);
}
