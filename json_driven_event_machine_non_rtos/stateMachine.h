
#pragma once

#ifndef stateMachine_h
#define stateMachine_h


#include "stateDataTypes.h"
// 4. Define the state machine function prototypes.
//    Any function that will be passed data from a user input will be passed the same jsonStateData_t structure as an argument.
// make sure every state named in step one has a prototype here!

// Required States


//#define TOTAL_NUM_STATES 22

// After finishing this list -> try running https://github.com/ImogenWren/json-state-machine/blob/main/state-machine-generator.py script to auto generate
// the StateMachine[] array, and template functions for each state!


//extern const uint16_t stateTableCount;


class stateMachine {
  public:
  // constructor
  stateMachine();


  stateDef_t smState = STATE_INIT;
  stateDef_t lastState;
  //stateHandler_t stateHandler[];  // ties together states with the state ENUM   // previously extern
  void change_state(stateDef_t new_state);

  void sm_Run(jsonStateData_t &stateData);

  // user defined state prototypes
  void sm_state_null(jsonStateData_t &stateData);
  void sm_state_init(jsonStateData_t &stateData);
  void sm_state_wait(jsonStateData_t &stateData);
  // Experiment Specific States
  void sm_state_set_fan(jsonStateData_t &stateData);
  void sm_state_set_yaw( jsonStateData_t &stateData);
  void sm_state_set_pitch(jsonStateData_t &stateData);
  void sm_state_stop(jsonStateData_t &stateData);
  void sm_state_bump( jsonStateData_t &stateData);
  void sm_state_set_load(jsonStateData_t &stateData);
  void sm_state_set_smooth( jsonStateData_t &stateData);
  // new states here now
  void sm_state_set_m_rntm(jsonStateData_t &stateData);
  void sm_state_set_gen_rots(jsonStateData_t &stateData);
  void sm_state_set_yaws_cmd(jsonStateData_t &stateData);
  void sm_state_set_pitch_cmd(jsonStateData_t &stateData);

  // Common & Utility States
  void sm_state_samplerate(jsonStateData_t &stateData);
  void sm_state_printrate(jsonStateData_t &stateData);
  void sm_state_start_stream(jsonStateData_t &stateData);
  void sm_state_stop_stream(jsonStateData_t &stateData);
  void sm_state_set_secret(jsonStateData_t &stateData);
  void sm_state_reset(jsonStateData_t &stateData);
  void sm_state_info(jsonStateData_t &stateData);
  void sm_state_help(jsonStateData_t &stateData);


  //stateHandler_t stateHandler[];
  typedef void (stateMachine::*stateFunc_t)(jsonStateData_t &stateData);

  typedef struct {
  stateDef_t State;                          //< Defines thestate enum
  stateFunc_t func;                              //void (*func)(stateMachine* self, jsonStateData_t &stateData);  //< Defines the function to run
} stateHandler_t;

  uint16_t stateTableCount = NUM_STATES;

  const stateHandler_t stateHandler[NUM_STATES] = {
    { STATE_NULL, &stateMachine::sm_state_null },
    { STATE_INIT, &stateMachine::sm_state_init },
    { STATE_WAIT, &stateMachine::sm_state_wait },
    { STATE_SET_FAN, &stateMachine::sm_state_set_fan },
    { STATE_SET_YAW, &stateMachine::sm_state_set_yaw },
    { STATE_SET_PITCH, &stateMachine::sm_state_set_pitch },
    { STATE_STOP, &stateMachine::sm_state_stop },
    { STATE_BUMP, &stateMachine::sm_state_bump },
    { STATE_SET_LOAD, &stateMachine::sm_state_set_load },
    { STATE_SET_SMOOTHING, &stateMachine::sm_state_set_smooth },

    { STATE_MOTOR_RUNTIME, &stateMachine::sm_state_set_m_rntm },
    { STATE_GEN_ROTATIONS, &stateMachine::sm_state_set_gen_rots },
    { STATE_YAW_CMNDED, &stateMachine::sm_state_set_yaws_cmd },
    { STATE_PITCH_CMNDED, &stateMachine::sm_state_set_pitch_cmd },

    { STATE_SAMPLERATE, &stateMachine::sm_state_samplerate },
    { STATE_PRINTRATE, &stateMachine::sm_state_printrate },
    { STATE_STARTSTREAM, &stateMachine::sm_state_start_stream },
    { STATE_STOPSTREAM, &stateMachine::sm_state_stop_stream },
    { STATE_SETSECRET, &stateMachine::sm_state_set_secret },
    { STATE_RESET, &stateMachine::sm_state_reset },
    { STATE_INFO, &stateMachine::sm_state_info },
    { STATE_HELP, &stateMachine::sm_state_help }
  };
  private:
};





#endif
