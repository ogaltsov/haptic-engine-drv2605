#include <Wire.h>
#include "Adafruit_DRV2605.h"

Adafruit_DRV2605 drv;

void setup() {
  Serial.begin(9600);
  Serial.println("Start");

  drv.begin();
  drv.setMode(DRV2605_MODE_REALTIME);
}

int rtp_index = 0;
uint8_t rtp[] = {
  21, 22, 23, 24, 25, 26, 27, 28, 25, 23, 21
};
bool forward = true;

void loop() {

  if (rtp_index >= 0 && rtp_index < sizeof(rtp)/sizeof(rtp[0])) {
    Serial.println(rtp[rtp_index]);
    
    for(uint8_t i = 0; i < 3; i++) {
      drv.setRealtimeValue(rtp[rtp_index]);
      delay(200);
      drv.setRealtimeValue(0);
      delay(5);
    }
    forward ? rtp_index++ : rtp_index--;

  } else {
    drv.setRealtimeValue(0x00);
    delay(3000);
    forward ? rtp_index-- : rtp_index++;
    forward = !forward;
  }
}