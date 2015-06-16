#include "SineEase.h"
#include "Tlc5940.h"
#include "tlc_fades.h"

TLC_CHANNEL_TYPE channel;
// CubicEase ease; // delay didesni
SineEase ease;

void setup() {
  Tlc.init();
  ease.setDuration(4);
  ease.setTotalChangeInPosition(4095);
  Serial.begin(9600);
  //  pinMode(9,OUTPUT);
}


void loop() {
  double easedPosition, t = 0;

  for (int i = 0; i < 200; i++) {
    easedPosition = ease.easeInOut(t);
    Serial.println(easedPosition);
    t += 0.02;
    setLeds(easedPosition);
    delay(5);
  }
  
  delay(1000);
  
  easedPosition=4095;
  for (int i = 199; i >= 0; i--) {
    easedPosition = ease.easeIn(t);
    Serial.println(easedPosition);
    t -= 0.02;
    setLeds(easedPosition);
    delay(5);
  }
  
  
  delay(2500);
}
void setLeds(int i) {
  Tlc.clear();
  for (uint8_t channel = 0; channel < 16; channel++) {
    Tlc.set(channel, i);

  }
  Tlc.update();
  tlc_updateFades();
}
