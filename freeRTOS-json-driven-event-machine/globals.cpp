
#include "globals.h"


QueueHandle_t QueueHandle;
const int QueueElements = 10;
const jsonStateData_t emptyData = {stateDef_t::STATE_NULL, dataTypes_t::EMPTY, 0, 0, 0.0, false, "", "", false};
jsonStateData_t nextState_data = emptyData;
// Object Declaration (+ associated global vars)
// Indicator LEDs
ledObject LEDS[4] = { ledObject(BLUE_LED_PIN), ledObject(GREEN_LED_PIN), ledObject(YELLOW_LED_PIN), ledObject(RED_LED_PIN) };


// jsonMessenger Object to handle incoming Serial JSON commands
jsonMessenger jsonRX;  // create a jsonMessenger object to handle commands received over Serial connection

// stateMachine Object now handles all state machine transitions
stateMachine sm;