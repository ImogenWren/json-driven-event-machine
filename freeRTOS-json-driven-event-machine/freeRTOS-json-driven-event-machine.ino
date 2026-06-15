/*   freeRTOS Queueing Function for jsonMessenger

Whenver a message is recieved from jsonMessenger, it is added to a queue in freeRTOS.
Seperate task unpacks data from queue and actions state
 
 Imogen Wren
 15/06/2026

*/

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
  // Create the queue which will have <QueueElements> number of elements, each of size `message_t` and pass the address to <QueueHandle>.
  QueueHandle = xQueueCreate(QueueElements, sizeof(jsonStateData_t));

  // Check if the queue was successfully created
  if (QueueHandle == NULL) {
    Serial.println("Queue could not be created. Halt.");
    while (1) {
      delay(1000);  // Halt at this point as is not possible to continue
    }
  }
  // Set up tasks to run independently.  // typical statck assignment = 2048
  xTaskCreate(task_enqueue_command, "Task Enqueue Command", 4096, NULL, 2, NULL);  //8192 working stacksize // (functionName, humanName, stacksize, parameter, priority (0-3), task handle) `uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);`
  xTaskCreate(task_dequeue_command, "Task Dequeue Command", 4096, NULL, 1, NULL);  // (functionName, humanName, stacksize, parameter, priority (0-3), task handle) `uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);`
  xTaskCreate(task_run_statemachine, "Task Run State Machine",4096, NULL, 2, NULL); 

  // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.
}


void loop() {
  // loop free to do other work
  delay(1000);
  // Serial.printf("Remaining stack words: %u\n", uxTaskGetStackHighWaterMark(NULL));
}
