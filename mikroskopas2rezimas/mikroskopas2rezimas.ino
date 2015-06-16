/*
    A simple 1-d oscilliscope: scan all the channels, setting the PWM output
    value to 4x the analog pin 0 value (0 - 1024 * 4 = 4096).  The value will
    fade to zero as the channels keep scanning.

    See the BasicUse example for hardware setup.

    Alex Leone <acleone ~AT~ gmail.com>, 2009-02-03 */

#include "Tlc5940.h"
#include "tlc_fades.h"

// which analog pin to use
#define ANALOG_PIN      0

// how many millis to strobe over all the LEDs
#define SCOPE_PERIOD    (3500 * NUM_TLCS)
#define LED_PERIOD      SCOPE_PERIOD / (NUM_TLCS * 16)

int state = 1; // jeigu state 1, tai pulsuojam, jeigu state 2 tai tunnel


TLC_CHANNEL_TYPE channel;

void setup()
{
  Tlc.init();
  setupUltrasound();
}

void loop()
{
 // loopUltrasound();

  uint32_t lastMillis = millis();

  
      // BEGIN 2 rezimas

      tlc_addFade(channel,                      // led channel
                  0,   // start fade value (0-4095)
                  4095,                            // end fade value (0-4095)
                  lastMillis + 0,               // start millis
                  lastMillis + (uint16_t)SCOPE_PERIOD / 5  // end millis
                 );

      tlc_addFade(channel,                      // led channel
                  4095,   // start fade value (0-4095)
                  0,                            // end fade value (0-4095)
                  lastMillis + (uint16_t)SCOPE_PERIOD / 4,               // start millis
                  lastMillis + (uint16_t)SCOPE_PERIOD / 2  // end millis
                 );

      //break;
  


 
  if (channel-- == 0) {
    channel = NUM_TLCS * 16;
  }
  uint32_t currentMillis;
  do {
    currentMillis = millis();
    tlc_updateFades(currentMillis);
  } while (currentMillis - lastMillis <= LED_PERIOD);

  // END 2 rezimas
}

