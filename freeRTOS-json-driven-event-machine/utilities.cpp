



#include "utilities.h"




void print_json_state_data(jsonStateData_t &data) {
  printf("CMD recieved: %i, %i, %i, %u, %f, %d, %s, %s, %d \n",
         data.stateEnum,
         data.data_type,
         data.signedInt,
         data.uInt,
         data.floatData,
         data.boolData,
         data.msg,
         data.auth,
         data.cmd_received);
}