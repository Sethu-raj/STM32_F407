/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Task Deletion FreeRTOS Example
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "task.h"

/* Private variables ---------------------------------------------------------*/
osThreadId defaultTaskHandle;

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
void StartDefaultTask(void const * argument);

/* USER CODE BEGIN 0 */

TaskHandle_t Task2Handle;

void Task1_Handler(void *params);
void Task2_Handler(void *params);

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  HAL_Init();

  SystemClock_Config();

  MX_GPIO_Init();

  /* Create the thread(s) */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */

  xTaskCreate(Task1_Handler,
              "Task1",
              128,
              NULL,
              1,
              NULL);

  xTaskCreate(Task2_Handler,
              "Task2",
              128,
              NULL,
              1,
              &Task2Handle);

  /* USER CODE END RTOS_THREADS */

  /* Start scheduler */
  osKernelStart();

  while (1)
  {

  }
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;

  RCC_OscInitStruct.HSIState = RCC_HSI_ON;

  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;

  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;

  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;

  RCC_OscInitStruct.PLL.PLLM = 8;

  RCC_OscInitStruct.PLL.PLLN = 50;

  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;

  RCC_OscInitStruct.PLL.PLLQ = 7;

  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK |
                                RCC_CLOCKTYPE_SYSCLK |
                                RCC_CLOCKTYPE_PCLK1 |
                                RCC_CLOCKTYPE_PCLK2;

  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;

  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;

  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;

  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /* Configure Output Level */
  HAL_GPIO_WritePin(GPIOD,
                    GPIO_PIN_12 | GPIO_PIN_13,
                    GPIO_PIN_RESET);

  /* Configure GPIO pins : PD12 PD13 */
  GPIO_InitStruct.Pin = GPIO_PIN_12 | GPIO_PIN_13;

  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;

  GPIO_InitStruct.Pull = GPIO_NOPULL;

  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
}

/* USER CODE BEGIN 4 */

void Task1_Handler(void *params)
{
    while(1)
    {
        HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);

        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

//void Task2_Handler(void *params)
//{
//    int count = 0;
//
//    while(1)
//    {
//        HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);
//
//        vTaskDelay(pdMS_TO_TICKS(1000));
//
//        count++;
//
//        if(count == 5)
//        {
//            vTaskDelete(NULL);
//        }
//    }
//}

void Task2_Handler(void *params)
{
    int count = 0;

    while(1)
    {
        HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);

        vTaskDelay(pdMS_TO_TICKS(500));

        count++;

        if(count == 10)
        {
            vTaskDelete(NULL);
        }
    }
}

/* USER CODE END 4 */

/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
void StartDefaultTask(void const * argument)
{
  for(;;)
  {
    osDelay(1);
  }
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  __disable_irq();

  while (1)
  {

  }
}

#ifdef  USE_FULL_ASSERT

void assert_failed(uint8_t *file, uint32_t line)
{

}
#endif
