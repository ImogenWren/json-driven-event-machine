
#include "globals.h"

// Object Declaration (+ associated global vars)
// Indicator LEDs
ledObject LEDS[4] = { ledObject(BLUE_LED_PIN), ledObject(GREEN_LED_PIN), ledObject(YELLOW_LED_PIN), ledObject(RED_LED_PIN) };


// jsonMessenger Object to handle incoming Serial JSON commands
jsonMessenger jsonRX;  // create a jsonMessenger object to handle commands received over Serial connection

// stateMachine Object now handles all state machine transitions
stateMachine sm;