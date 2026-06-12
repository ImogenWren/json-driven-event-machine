/* stateMachine.cpp

Here use the templates to fully define the contents of each state. 

Good states should set variables and do things quickly, then exit so the state machine can continue to run.

Blocking states are acceptable if you understand why they will be blocking and account for this within the implementation.

e.g. In these states, the pulse state is blocking while it sends one wave out. This is okay because this event happens very quickly and then exits immediatly
 

*/

#include "stateMachine.h"
#include "stateDatatypes.h"
#include "globals.h"


stateMachine::stateMachine() {
}


void stateMachine::sm_state_null(jsonStateData_t &stateData) {
  Serial.println(F("ERROR: NULL STATE!"));
  stateData.uInt++;
  smState = STATE_WAIT;
}

// Init state, only called at startup
void stateMachine::sm_state_init(jsonStateData_t &stateData) {
  if (lastState != smState) {
#if DEBUG_STATES == true
    Serial.println("state: INIT");
#endif
    stateData.uInt++;
    lastState = smState;
  }

  smState = STATE_WAIT;
}




// State Wait is the default state for this program
void stateMachine::sm_state_wait(jsonStateData_t &stateData) {
  if (lastState != smState) {
    stateData.uInt++;
    // If first iteration print state machine status
#if DEBUG_STATES == true
    Serial.println(F("state: WAIT"));
#endif
#if COMMAND_HINTS == true  // print suggested commands
    Serial.println(F("\nEnter cmd in format:"));
    jsonRX.print_cmds();
#endif
    lastState = smState;
  }
}



void stateMachine::sm_state_set_fan(jsonStateData_t &stateData) {
  if (lastState != smState) {
#if DEBUG_STATES == true
    Serial.println(F("state: SETFAN"));
#endif
    // Serial.print("abs_diff: ");
    // Serial.println(absDiff(0.0, stateData.floatData));
    /*
    if (stateData.floatData > fan_speed_min) {
      if (escStatus == ESC_DISABLED) {
        enable_esc();
        escStatus = ESC_ENABLED;
      }
      if (stateData.floatData <= fan_speed_max && stateData.floatData > fan_speed_min) {
        fan_speed_target = stateData.floatData;
        esc_active_time_mS = millis();
        lastMotorCountTime_mS = millis();
        //fan_speed_current = fan_speed_bump;  // function in main loop to slowly move esc towards target speed
        esc.write(fan_speed_current);
        escStatus = ESC_BUMP;
      } else {
        json_error("WARNING", "Fan speed commanded out of range");
      }
    } else if (absDiff(0.0, stateData.floatData) < 0.9 || stateData.floatData <= 0.0) {  // is value is close to 0 then just set to zero and assume fan is stopping
      fan_speed_target = 0;
      escStatus = ESC_STOPPING;
    } else {
      json_error("WARNING", "Fan speed commanded out of range");
    }
    lastState = smState;  
  */
  }
  smState = STATE_WAIT;
}

void stateMachine::sm_state_set_yaw(jsonStateData_t &stateData) {
  if (lastState != smState) {
#if DEBUG_STATES == true
    Serial.println(F("state: SETYAW"));
#endif

   // if (stateData.floatData >= yaw_servo_min && stateData.floatData <= yaw_servo_max) {
    //  yaw_servo_target = stateData.floatData;
      // lifeCounters.yawsCommanded++;  // shouldnt interact with this directly but otherwise will need a function for each data
   // } else {
      // json_error("WARNING", "yaw target out of range");
 //   }
    lastState = smState;
  }
  smState = STATE_WAIT;
}

void stateMachine::sm_state_set_pitch(jsonStateData_t &stateData) {
  if (lastState != smState) {
#if DEBUG_STATES == true
    Serial.println(F("state: SETPITCH"));
#endif
 //   if (stateData.floatData >= pitch_servo_min && stateData.floatData <= pitch_servo_max) {
   //   pitch_servo_target = stateData.floatData;
      //   lifeCounters.pitchCommanded++;  // shouldnt interact with this directly but otherwise will need a function for each data
 //   } else {
      //    json_error("WARNING", "pitch target out of range");
  //  }
    lastState = smState;
  }
  smState = STATE_WAIT;
}

void stateMachine::sm_state_stop(jsonStateData_t &stateData) {
  if (lastState != smState) {
#if DEBUG_STATES == true
    Serial.println(F("state: STOP"));
#endif
    // stateData.uInt++;
    //  fan_speed_target = 0;
    // fan_speed_current = 0;  // function in main loop to slowly move esc towards target speed
    /// esc.write(0);


  //  escStatus = ESC_STOPPED;
    lastState = smState;
  }
  smState = STATE_WAIT;
}

// this can be inconsistant when initial velocity is at 0 but otherwise seems reliable
void stateMachine::sm_state_bump(jsonStateData_t &stateData) {
  if (lastState != smState) {
#if DEBUG_STATES == true
    Serial.println(F("state: BUMP"));
#endif
    stateData.uInt++;
 //   if (escStatus == ESC_DISABLED) {
   //   enable_esc();
  //    escStatus = ESC_ENABLED;
  //  }
    // esc_active_time_mS = millis();
    //   fan_speed_current = fan_speed_bump;  // function in main loop to slowly move esc towards target speed
    //esc.write(fan_speed_current);
    //   escStatus = ESC_BUMP;
    lastState = smState;
  }
  smState = STATE_WAIT;
}

void stateMachine::sm_state_set_load(jsonStateData_t &stateData) {
  if (lastState != smState) {
#if DEBUG_STATES == true
    Serial.println(F("state: SETLOAD"));
#endif
    if (stateData.boolData) {
     // enable_load();
    } else {
   //   disable_load();
    }
    lastState = smState;
  }
  smState = STATE_WAIT;
}

void stateMachine::sm_state_set_smooth(jsonStateData_t &stateData) {
  if (lastState != smState) {
#if DEBUG_STATES == true
    Serial.println(F("state: SETSMOOTH"));
#endif
    if (stateData.boolData) {
      //   enable_smoothing();
    } else {
      // disable_smoothing();
    }
    lastState = smState;
  }
  smState = STATE_WAIT;
}



void stateMachine::sm_state_set_m_rntm(jsonStateData_t &stateData) {
  if (lastState != smState) {
#if DEBUG_STATES == true
    Serial.println(F("state: SET_MOTOR_RUNTIME"));
#endif
    if (stateData.floatData >= 0) {
    //  if (memory.check_secret(stateData.auth)) {
        // logData_t stats = lifeLog.get_current();          // get the current stats
        // stats.motorSeconds = stateData.floatData * 3600;  // update the value that needs to be updated
        // lifeLog.write_log(stats);                         // write the updated value to memory
    //  } else {
    //    json_error("WARNING", "Incorrect Secret");
   //   }
    } else {
    //  json_error("warning", "motor runtime data not in range");
    }
    lastState = smState;
  }
  smState = STATE_WAIT;
}



void stateMachine::sm_state_set_gen_rots(jsonStateData_t &stateData) {
  if (lastState != smState) {
#if DEBUG_STATES == true
    Serial.println(F("state: SET_GEN_ROTS"));
#endif
    if (stateData.signedInt >= 0) {
    //  if (memory.check_secret(stateData.auth)) {
     //   logData_t stats = lifeLog.get_current();         // get the current stats
     //   stats.generatorRotations = stateData.signedInt;  // update the value that needs to be updated
     //   gen_rotations = 0;
   //     lifeLog.write_log(stats);  // write the updated value to memory
   //   } else {
     //   json_error("WARNING", "Incorrect Secret");
     // }
    } else {
    //  json_error("warning", "Generator Rotations data not in range");
    }
    lastState = smState;
  }
  smState = STATE_WAIT;
}

void stateMachine::sm_state_set_yaws_cmd(jsonStateData_t &stateData) {
  if (lastState != smState) {
#if DEBUG_STATES == true
    Serial.println(F("state: SET_YAWS_CMD"));
#endif
    if (stateData.signedInt >= 0) {
   //   if (memory.check_secret(stateData.auth)) {
   //    logData_t stats = lifeLog.get_current();    // get the current stats
    //    stats.yawsCommanded = stateData.signedInt;  // update the value that needs to be updated
    //    lifeCounters.yawsCommanded = 0;
    //    lifeLog.write_log(stats);  // write the updated value to memory
     // } else {
    //    json_error("WARNING", "Incorrect Secret");
     // }
    } else {
   //   json_error("warning", "Yaws Commanded data not in range");
    }
    lastState = smState;
  }
  smState = STATE_WAIT;
}

void stateMachine::sm_state_set_pitch_cmd(jsonStateData_t &stateData) {
  if (lastState != smState) {
#if DEBUG_STATES == true
    Serial.println(F("state: SET_PITCH_CMD"));
#endif
    if (stateData.signedInt >= 0) {
    //  if (memory.check_secret(stateData.auth)) {
   //     logData_t stats = lifeLog.get_current();     // get the current stats
   //     stats.pitchCommanded = stateData.signedInt;  // update the value that needs to be updated
   //     lifeCounters.pitchCommanded = 0;
   //     lifeLog.write_log(stats);  // write the updated value to memory
    //  } else {
  //      json_error("WARNING", "Incorrect Secret");
    //  }
    } else {
  //    json_error("warning", "Pitch Commanded data not in range");
    }
    lastState = smState;
  }
  smState = STATE_WAIT;
}







// Change the samplerate of streamed or snapshotted data (Init at 10 Hz)
void stateMachine::sm_state_samplerate(jsonStateData_t &stateData) {
  if (lastState != smState) {
#if DEBUG_STATES == true
    Serial.println(F("st: SAMPLERATE"));
#endif
    lastState = smState;
  }
  if (stateData.uInt < 1 || stateData.uInt > 200) {
    // errors.set_error(false, -10, "Out of Bounds Sample Rate Commanded", errors.WARNING, "state-samplerate");
    //  errors.print_json_status();
 // } else if (stateData.uInt < print_rate_Hz) {
    //  errors.set_error(false, -10, "Cannot set sample rate less than print rate", errors.WARNING, "state-samplerate");
    //  errors.print_json_status();
  } else {
    //   sampleRate_Hz = stateData.uInt;
    // sampleDelay_mS = 1000 / sampleRate_Hz;
    //   sampleDelay_mS = 1E3 / sampleRate_Hz - SAMPLE_DELAY_OFFSET;
    //   num_samples_req = uint8_t(sampleRate_Hz / print_rate_Hz);  // Number of samples required to collect between each print cycle
  }
  smState = STATE_WAIT;
}



// Change the samplerate of streamed or snapshotted data (Init at 10 Hz)
void stateMachine::sm_state_printrate( jsonStateData_t &stateData) {
  if (lastState != smState) {
#if DEBUG_STATES == true
    Serial.println(F("st: PRINT RATE"));
#endif
    lastState = smState;
  }
  if (stateData.uInt < 1 || stateData.uInt > 50) {
    //   errors.set_error(false, -10, "Out of Bounds Print Rate Commanded", errors.WARNING, "state-printrate");
    //   errors.print_json_status();
  }// else if (stateData.uInt > sampleRate_Hz) {
    //   errors.set_error(false, -10, "Cannot set print rate greater than sample rate", errors.WARNING, "state-printrate");
    //   errors.print_json_status();
 // } else {
    //  print_rate_Hz = stateData.uInt;
    //  print_delay_mS = 1000 / print_rate_Hz;
    //  num_samples_req = uint8_t(sampleRate_Hz / print_rate_Hz);  // Number of samples required to collect between each print cycle
  //}
  smState = STATE_WAIT;
}





// Start streaming data
void stateMachine::sm_state_start_stream(jsonStateData_t &stateData) {
  if (lastState != smState) {
#if DEBUG_STATES == true
    Serial.println(F("st: STARTSTREAM"));
#endif
    stateData.uInt++;
    lastState = smState;
  }
 // streaming_active = true;
 // samples_written = 0;  // start sampling again, wondering if this is the cause of the issues
  //  snapshot_timer_mS = jsonStateData_t.signedInt;
  smState = STATE_WAIT;
}



// Stop streaming data
void stateMachine::sm_state_stop_stream( jsonStateData_t &stateData) {
  if (lastState != smState) {
#if DEBUG_STATES == true
    Serial.println(F("state: STOPSTREAM"));
#endif
    stateData.uInt++;
    lastState = smState;
  }
 // streaming_active = false;
  // snapshot_timer_mS = 0;
  smState = STATE_WAIT;
}


// NEWER FUNCTIONS from here -------------------------------->>>>

// Trigger a snapshot of data to be taken over X amount of time
void stateMachine::sm_state_set_secret(jsonStateData_t &stateData) {
  if (lastState != smState) {
#if DEBUG_STATES == true
    Serial.println(F("state: SET SECRET"));
#endif
    lastState = smState;
    if (stateData.msg[0] == '\0') {  //empty string
      Serial.println(F("{\"WARNING\":\"Secret not Set\"}"));
      smState = STATE_WAIT;
      return;
    } else {
  //    memory.set_secret(stateData.msg);
    }
  }
  smState = STATE_WAIT;
}

void stateMachine::sm_state_reset(jsonStateData_t &stateData) {
  if (lastState != smState) {
#if DEBUG_STATES == true
    Serial.println(F("state: RESET"));
#endif
    stateData.uInt++;
    lastState = smState;
  }
  smState = STATE_WAIT;
}



// Print the commands list to the Serial Output
void stateMachine::sm_state_info(jsonStateData_t &stateData) {
  if (lastState != smState) {
#if DEBUG_STATES == true
    Serial.println(F("state: help"));
#endif
    stateData.uInt++;
    lastState = smState;
    //  sample_data();
 //   update_json(1, smState);
  }

  smState = STATE_WAIT;
}



// Print the commands list to the Serial Output
void stateMachine::sm_state_help(jsonStateData_t &stateData) {
  if (lastState != smState) {
#if DEBUG_STATES == true
    Serial.println(F("state: help"));
#endif
    stateData.uInt++;
    lastState = smState;
  }
  //print_cmds();
 // print_cmds2();
  smState = STATE_WAIT;
}


void stateMachine::change_state(stateDef_t new_state){
  smState = new_state;
}



// 6. Finally define the state machine function
void stateMachine::sm_Run(jsonStateData_t &stateData) {
  if (smState < NUM_STATES) {
#if DEBUG_STATE_MACHINE == true
    if (lastState != smState) {
      char buffer[14];
      Serial.print("{\"sm\":\"");
  //    strcpy_P(buffer, (char *)pgm_read_ptr(&(stateNames[smState])));  // Necessary casts and dereferencing, just copy.
 //     Serial.print(buffer);
      //  Serial.print(stateNames[smState]);   // old RAM heavy version
      Serial.println(F("\"}"));
    }
#endif
    (this->*stateHandler[smState].func)(stateData);

  } else {
    sm_state_wait(stateData);
    Serial.println("sm: Exception -> NUM_STATES exceeded");
  }
}
