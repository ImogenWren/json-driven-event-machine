
#include "tasks.h"


void task_enqueue_command(void *pvParameters) {
  jsonStateData_t nextState_data;
  for (;;) {
    jsonRX.jsonReadSerialLoop(nextState_data);
    if (nextState_data.cmd_received) {
      //jsonRX.printJSONdata(&nextState_data);
      print_json_state_data(nextState_data);
      // Check if the queue exists AND if there is any free space in the queue
      Serial.printf("Stack low water: %u bytes\n",
                    uxTaskGetStackHighWaterMark(NULL) * 4);
      if (QueueHandle != NULL && uxQueueSpacesAvailable(QueueHandle) > 0) {
        // The queue element needs to be passed as pointer to void.
        // The last parameter states how many milliseconds should wait (keep trying to send) if is not possible to send right away.
        // When the wait parameter is 0 it will not wait and if the send is not possible the function will return errQUEUE_FULL
        int ret = xQueueSend(QueueHandle, (void *)&nextState_data, 1000);
        if (ret == pdTRUE) {
          // The message was successfully sent.
          Serial.println("message enqueued");
        } else if (ret == errQUEUE_FULL) {
          // Since we are checking uxQueueSpacesAvailable this should not occur, however if more than one task should
          //   write into the same queue it can fill-up between the test and actual send attempt
          Serial.println("The `task_enqueue_command` was unable to send data into the Queue");
        }          // Queue send check
      }            // Queue sanity check
    } else {       // no command has been recevied;
      delay(100);  // allow other tasks to run
    }              // new message check
  }                // infinite loop
}





void task_dequeue_command(void *pvParameters) {
  for (;;) {
    // jsonStateData_t nextState_data;   going to make this global
    // One approach would be to poll the function (uxQueueMessagesWaiting(QueueHandle) and call delay if nothing is waiting.
    // The other approach is to use infinite time to wait defined by constant `portMAX_DELAY`:
    if (QueueHandle != NULL) {                                               // Sanity check just to make sure the queue actually exists
      int ret = xQueueReceive(QueueHandle, &nextState_data, portMAX_DELAY);  //portMAX_DELAY
      Serial.printf("Stack low water: %u bytes\n", uxTaskGetStackHighWaterMark(NULL) * 4);
      if (ret == pdPASS) {
        // The message was successfully received
        Serial.println("message dequeued");
        jsonRX.printStateData(nextState_data);
        //print_json_state_data(nextState_data);
        sm.change_state(nextState_data.stateEnum);
      } else if (ret == pdFALSE) {
        Serial.println("The `task_dequeue_command` was unable to receive data from the Queue");
      }
    }  // Sanity check
  }    // Infinite loop
}


void task_run_statemachine(void *pvParameters) {
  for (;;) {
    sm.sm_Run(nextState_data);
  }
}
