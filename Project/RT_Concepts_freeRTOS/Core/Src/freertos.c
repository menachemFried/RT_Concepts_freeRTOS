/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for DispatcherTask */
osThreadId_t DispatcherTaskHandle;
const osThreadAttr_t DispatcherTask_attributes = {
  .name = "DispatcherTask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for AmbulanceTask */
osThreadId_t AmbulanceTaskHandle;
const osThreadAttr_t AmbulanceTask_attributes = {
  .name = "AmbulanceTask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for FireDeptTask */
osThreadId_t FireDeptTaskHandle;
const osThreadAttr_t FireDeptTask_attributes = {
  .name = "FireDeptTask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for LoggerTask */
osThreadId_t LoggerTaskHandle;
const osThreadAttr_t LoggerTask_attributes = {
  .name = "LoggerTask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for DispatcherQueue */
osMessageQueueId_t DispatcherQueueHandle;
const osMessageQueueAttr_t DispatcherQueue_attributes = {
  .name = "DispatcherQueue"
};
/* Definitions for AmbulanceQueue */
osMessageQueueId_t AmbulanceQueueHandle;
const osMessageQueueAttr_t AmbulanceQueue_attributes = {
  .name = "AmbulanceQueue"
};
/* Definitions for PoliceQueue */
osMessageQueueId_t PoliceQueueHandle;
const osMessageQueueAttr_t PoliceQueue_attributes = {
  .name = "PoliceQueue"
};
/* Definitions for FireQueue */
osMessageQueueId_t FireQueueHandle;
const osMessageQueueAttr_t FireQueue_attributes = {
  .name = "FireQueue"
};
/* Definitions for LogQueue */
osMessageQueueId_t LogQueueHandle;
const osMessageQueueAttr_t LogQueue_attributes = {
  .name = "LogQueue"
};
/* Definitions for EventGenTimer */
osTimerId_t EventGenTimerHandle;
const osTimerAttr_t EventGenTimer_attributes = {
  .name = "EventGenTimer"
};
/* Definitions for AmbulanceSem */
osSemaphoreId_t AmbulanceSemHandle;
const osSemaphoreAttr_t AmbulanceSem_attributes = {
  .name = "AmbulanceSem"
};
/* Definitions for PoliceSem */
osSemaphoreId_t PoliceSemHandle;
const osSemaphoreAttr_t PoliceSem_attributes = {
  .name = "PoliceSem"
};
/* Definitions for myCountingSem03 */
osSemaphoreId_t myCountingSem03Handle;
const osSemaphoreAttr_t myCountingSem03_attributes = {
  .name = "myCountingSem03"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void StartTask02(void *argument);
void StartTask03(void *argument);
void StartTask04(void *argument);
void StartTask05(void *argument);
void Callback01(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* creation of AmbulanceSem */
  AmbulanceSemHandle = osSemaphoreNew(4, 4, &AmbulanceSem_attributes);

  /* creation of PoliceSem */
  PoliceSemHandle = osSemaphoreNew(3, 3, &PoliceSem_attributes);

  /* creation of myCountingSem03 */
  myCountingSem03Handle = osSemaphoreNew(2, 2, &myCountingSem03_attributes);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* Create the timer(s) */
  /* creation of EventGenTimer */
  EventGenTimerHandle = osTimerNew(Callback01, osTimerPeriodic, NULL, &EventGenTimer_attributes);

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* creation of DispatcherQueue */
  DispatcherQueueHandle = osMessageQueueNew (10, sizeof(uint16_t), &DispatcherQueue_attributes);

  /* creation of AmbulanceQueue */
  AmbulanceQueueHandle = osMessageQueueNew (5, sizeof(uint16_t), &AmbulanceQueue_attributes);

  /* creation of PoliceQueue */
  PoliceQueueHandle = osMessageQueueNew (5, sizeof(uint16_t), &PoliceQueue_attributes);

  /* creation of FireQueue */
  FireQueueHandle = osMessageQueueNew (5, sizeof(uint16_t), &FireQueue_attributes);

  /* creation of LogQueue */
  LogQueueHandle = osMessageQueueNew (20, sizeof(uint16_t), &LogQueue_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of DispatcherTask */
  DispatcherTaskHandle = osThreadNew(StartTask02, NULL, &DispatcherTask_attributes);

  /* creation of AmbulanceTask */
  AmbulanceTaskHandle = osThreadNew(StartTask03, NULL, &AmbulanceTask_attributes);

  /* creation of FireDeptTask */
  FireDeptTaskHandle = osThreadNew(StartTask04, NULL, &FireDeptTask_attributes);

  /* creation of LoggerTask */
  LoggerTaskHandle = osThreadNew(StartTask05, NULL, &LoggerTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartTask02 */
/**
* @brief Function implementing the DispatcherTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask02 */
void StartTask02(void *argument)
{
  /* USER CODE BEGIN StartTask02 */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartTask02 */
}

/* USER CODE BEGIN Header_StartTask03 */
/**
* @brief Function implementing the AmbulanceTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask03 */
void StartTask03(void *argument)
{
  /* USER CODE BEGIN StartTask03 */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartTask03 */
}

/* USER CODE BEGIN Header_StartTask04 */
/**
* @brief Function implementing the FireDeptTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask04 */
void StartTask04(void *argument)
{
  /* USER CODE BEGIN StartTask04 */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartTask04 */
}

/* USER CODE BEGIN Header_StartTask05 */
/**
* @brief Function implementing the LoggerTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTask05 */
void StartTask05(void *argument)
{
  /* USER CODE BEGIN StartTask05 */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartTask05 */
}

/* Callback01 function */
void Callback01(void *argument)
{
  /* USER CODE BEGIN Callback01 */

  /* USER CODE END Callback01 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

