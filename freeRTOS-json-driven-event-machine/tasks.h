


#pragma once

#ifndef tasks_h
#define tasks_h


#include "globals.h"


// task prototypes for RTOS
void task_enqueue_command(void *pvParameters);
void task_dequeue_command(void *pVParameters);
void task_run_statemachine(void *pvParameters);

#endif