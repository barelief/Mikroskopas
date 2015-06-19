#include <firFilter.h>

firFilter Filter;

#include <NewPing.h>

#define TRIGGER_PIN  A7  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     5  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 100 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

// --- INIT TLCs

#include "Tlc5940.h"
#include "tlc_fades.h"

// which analog pin to use
#define ANALOG_PIN      0

// how many millis to strobe over all the LEDs
#define SCOPE_PERIOD    (3000 * NUM_TLCS)
#define LED_PERIOD      SCOPE_PERIOD / (NUM_TLCS * 16)


TLC_CHANNEL_TYPE channel;

bool pulseMode = true;
uint32_t fadeOutPulseMode = 0;

void setup() {
  Serial.begin(9600); // Open serial monitor at 115200 baud to see ping results.
  setupTLC();
  setupLedIdleMode();
  Filter.begin();
}

// smooth

//eof

void loop() {
  //delay(50);                      // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  //Serial.print("Ping: ");
  int cm = uS / US_ROUNDTRIP_CM;

  int cmFiltered = Filter.run(cm);

  if (cmFiltered > 0  && cmFiltered < 90)

  {
    pulseMode = true;
    Serial.print(cmFiltered); // Convert ping time to distance in cm and print result (0 = outside set distance range)
    //Serial.print(" - ");
    Serial.println();
    loopTLC();
  }

  else
  {
    if (pulseMode)
    {
      pulseMode = false;
      fadeOutPulseMode = millis();
    }

    if (channel == 24 && (millis() - fadeOutPulseMode) > LED_PERIOD )
    {
      // pulseMode = false;
      loopLedIdleMode();
    } else
      loopTLC();
    //if (channel == 0)

  }


}




