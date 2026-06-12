/*  globals.h
      Define all user set values, global constants, global vars, included libraries and global objects

      Imogen Heard
      21/03/2025
*/

#pragma once

#ifndef globals_h
#define globals_h


//#pragma "Use ESP32 Version 3.x.x"

// Imported Libraries
#include <WiFi.h>         // only here to turn off periferals
#include <ArduinoJson.h>  // installed version 6.21.5 [Arduino Library Manager]
#include <ledObject.h>



// Included Headers (Called from within any JSON-state-machine header or class)
#include "jsonMessenger.h"  // jsonMessenger also relies on variables desifined in jsonConfig
#include "stateMachine.h"


// Program Attributes
#define PROGRAM_NAME "RTOS json-driven event machine"
#define FIRMWARE_VERSION "0.0.0"
#define DEVELOPER "Imogen-Wren"





// Hardware Definitions
// Interrupt Pins
// On ESP32 all input pins can be used as interrupts
// ESP32 Pins & IOs
//      name   num  // [x] used?  Description
#define GPIO36 36  // [x]        Input only (VP)
#define GPIO39 39  // []         Input only (VN)
#define GPIO34 34  // [x]         Input only
#define GPIO35 35  // [x]         Input only
#define GPIO32 32  // [x]         ADC, RTC       PWM GOOD
#define GPIO33 33  // [x]         ADC, RTC       PWM GOOD
#define GPIO25 25  // []-         DAC1, ADC     GOOD FOR PWM
#define GPIO26 26  // []-         DAC2, ADC     GOOD FOR PWM
#define GPIO27 27  // [x]         ADC            GOOD FOR PWM
#define GPIO14 14  // [x]         ADC, HSPI CLK
#define GPIO12 12  // [x]         ADC, HSPI MISO (boot strapping pin)   AVOID -> flash voltage selection
#define GPIO13 13  // [x]         ADC, HSPI MOSI
#define GPIO15 15  // [x]         ADC, HSPI CS (boot strapping pin)      AVOID -> bootstrapping
#define GPIO2 2    // [x]         ADC, boot strapping pin, onboard LED   AVOID -> bootstrapping
#define GPIO4 4    // [x]         ADC                                    AVOID ??
#define GPIO16 16  // []         UART2 RX
#define GPIO17 17  // [x]         UART2 TX
#define GPIO5 5    // [x]         VSPI CS                                AVOID 6-11 -> internal flash  AVOID USING PWM/SERVO
#define GPIO18 18  // []         VSPI CLK                                   AVOID USING PWM/SERVO
#define GPIO19 19  // [x]         VSPI MISO                                      AVOID USING PWM/SERVO
#define GPIO21 21  // [x]         I2C SDA
#define GPIO22 22  // [x]         I2C SCL
#define GPIO23 23  // [x]         VSPI MOSI                                   AVOID USING PWM/SERVO

#define GPIO1 1  // UART0 TX (programming / serial)
#define GPIO3 3  // UART0 RX (programming / serial)

#define GPIO0 0  // Boot button, strapping pin

#define SDA 21  // 27
#define SCL 22  //26

#define SDA_DEPREC 27  // 21  // pin conflicts with GPIO 19, so not used for i2c, but set as INPUT for high impedence so MAIN and SPARE i2c can be shorted together to allow use of i2c header terminal blocks
#define SCL_DEPREC 26  //22

// LED / Indicators
//#define LED_BUILTIN 13
const int BLUE_LED_PIN = GPIO33;    // Used as visible UI element, flashes when CMD received
const int GREEN_LED_PIN = GPIO17;   // Power generation level indicator
const int YELLOW_LED_PIN = GPIO12;  // Power generation level indicator
const int RED_LED_PIN = GPIO5;      // CHANGED DUE TO i2C ERROR GPIO5;   GPIO16;   // Power generation level indicator
// LED pins will all be treated as ledObject::LEDS



// Unused hardware pins
//const int GPIO_1 = 3;
//const int GPIO_2 = 13;

//const int AI_1 = A1;
//const int AI_2 = 36;
//const int AI_3 = 39;





// Limits & Timeouts
#define LIMITS_ENABLED true

// User Options & Program Config
// JSON Reporting
#define PRINT_JSON true
#define PRETTY_PRINT_JSON false
#define JSON_TX_BUFFER_SIZE 2000


// Sample & Printing Rates
#define INIT_SAMPLE_RATE_Hz 1
#define INIT_PRINT_RATE_Hz 1


// Utility
#define EEPROM_ADDRESS 0xFF  // EEPROM location for calibration data if required

// Debugging
#define DEBUG_STATES false
#define DEBUG_STATE_MACHINE false

// Object Declaration (+ associated global vars)
// Indicator LEDs
extern ledObject LEDS[4];
// jsonMessenger Object to handle incoming Serial JSON commands
extern jsonMessenger jsonRX;  // create a jsonMessenger object to handle commands received over Serial connection
// stateMachine
extern stateMachine sm;



// Typedef for accessing LEDS[x] in a more user friendly way LEDS[LED_BLUE].turnOn(); etc
typedef enum {
  LED_BLUE,
  LED_GREEN,
  LED_YELLOW,
  LED_RED
} ledDef_t;




//#include "states.h"  // State machine pulls from globals and headers describing hardware functions
//#include "stateTable.h"


#endif