
#include "globals.h"
#include <stdint.h>

void setup() {
  WiFi.mode(WIFI_OFF);  // disable wifi & bluetooth periferals
  btStop();
  Serial.begin(115200);
  delay(2000);
  Serial.print(PROGRAM_NAME);
  Serial.print(" V");
  Serial.print(FIRMWARE_VERSION);
  Serial.print(" by: ");
  Serial.println(DEVELOPER);
  jsonRX.jsonBegin();
}

void loop() {
  jsonStateData_t nextState_data = jsonRX.jsonReadSerialLoop();
  if (nextState_data.cmd_received) {
    printf("CMD recieved: %i, %i, %i, %u, %f, %d, %s, %s, %d \n",
           nextState_data.stateEnum,
           nextState_data.data_type,
           nextState_data.signedInt,
           nextState_data.uInt,
           nextState_data.floatData,
           nextState_data.boolData,
           nextState_data.msg,
           nextState_data.auth,
           nextState_data.cmd_received);
    sm.change_state(nextState_data.stateEnum);
  }
  sm.sm_Run(nextState_data);
}


