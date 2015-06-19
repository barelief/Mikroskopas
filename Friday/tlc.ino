/// TLCs

// ----- PULSE REZIMAS




void setupTLC()
{
  Tlc.init();

}

void resetLeds()
{
  for (int i = 0; i < 16; i++)
  {
    tlc_addFade(i, 0, 0, 0, 0);
  }
}

void loopTLC()
{
  //loopSensor();

  uint32_t lastMillis = millis();


  // BEGIN 2 rezimas



  tlc_addFade(channel,                      // led channel
              0,   // start fade value (0-4095)
              4095,                            // end fade value (0-4095)
              lastMillis + 0,               // start millis
              lastMillis + (uint16_t)SCOPE_PERIOD / 4   // end millis
             );

  tlc_addFade(channel,                      // led channel
              4095,   // start fade value (0-4095)
              0,                            // end fade value (0-4095)
              lastMillis + (uint16_t)SCOPE_PERIOD / 4,               // start millis
              lastMillis + (uint16_t)SCOPE_PERIOD / 2  // end millis
             );

  //break;


  if (channel++ == 24) {
    channel = 0;
  }


  uint32_t currentMillis;
  do {
    currentMillis = millis();
    tlc_updateFades(currentMillis);
  } while (currentMillis - lastMillis <= LED_PERIOD);

  // END 2 rezimas
}



// ---------- IDLE rezimas

#include "SineEase.h"
#include "Tlc5940.h"
#include "tlc_fades.h"

//TLC_CHANNEL_TYPE channel;
// CubicEase ease; // delay didesni
SineEase ease;

void setupLedIdleMode() {
  Tlc.init();
  ease.setDuration(4);
  ease.setTotalChangeInPosition(4096);
  Serial.begin(9600);
  //  pinMode(9,OUTPUT);
}

void loopLedIdleMode() {
  double easedPosition, t = 0;

  for (int i = 0; i < 200; i++) {
    easedPosition = ease.easeInOut(t);
    //Serial.println(easedPosition);
    t += 0.02;
    setLeds(easedPosition);
    delay(15);
  }

  for (int i = 199; i >= 0; i--) {
    easedPosition = ease.easeIn(t);
    //Serial.println(easedPosition);
    t -= 0.02;
    setLeds(easedPosition);
    delay(15);
  }


  delay(1000); // urte prase ilgiau palaikyti cia
  channel = 16;

}
void setLeds(int i) {
  Tlc.clear();
  for (uint8_t channel = 0; channel < 16; channel++) {
    Tlc.set(channel, i);
    //Serial.print("set: ");
    //Serial.println(i);
  }
  Tlc.update();
  //  tlc_updateFades();
}

void clearTLC()
{
  Tlc.clear();
  for (int i = 0; i < 16; i++)
    Tlc.set(i, 0);
  Tlc.update();
}
