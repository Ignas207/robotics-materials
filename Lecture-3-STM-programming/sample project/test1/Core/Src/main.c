/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "main.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "VL53L1X.h"
#include <stdio.h>
#include <string.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

#define SET_PWM_DUTY(duty)((TIM2->CCR1 = (6399U / 100U) * duty))

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_I2C1_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */

  // const char testMsg[] = "Hello there!\n";
  // char buff[500] = {0};

  VL53L1X sensor0;
  VL53L1X sensor1;

  TOF_InitStruct(&sensor0, &hi2c1, 0x32, VL53L0X0_XHUT_GPIO_Port, VL53L0X0_XHUT_Pin);
  TOF_InitStruct(&sensor1, &hi2c1, 0x34, VL53L0X1_XHUT_GPIO_Port, VL53L0X1_XHUT_Pin);

  VL53L1X* sensors[] = {&sensor0, &sensor1};
  TOF_BootMultipleSensors(sensors, 2);

  // TOF_TurnOff(&sensor0);
  // TOF_TurnOff(&sensor1);

  // TOF_BootSensor(&sensor0);
  // HAL_Delay(10);
  // TOF_BootSensor(&sensor1);

  uint16_t sensor0_Data = 0;
  uint16_t sensor1_Data = 0;

  HAL_GPIO_WritePin(MOTOR_DIRECTION_GPIO_Port, MOTOR_DIRECTION_Pin, 1);
  // TIM2->CCR1 = 3200;
  HAL_Delay(10);
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);

  LOG_INFO("We are starting!\n");
  LOG_ERROR("This is an error!\n");
  LOG_EVENT("This is an event!\n");
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

    // HAL_GPIO_TogglePin(MOTOR_DIRECTION_GPIO_Port, MOTOR_DIRECTION_Pin);

    for (uint32_t i = 0; i < 6400; i += 20)
    {
      TIM2->CCR1 = i;
      HAL_Delay(1);
    }


	  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, 1);
    sensor0_Data = TOF_GetDistance(&sensor0);
    HAL_Delay(5);
    sensor1_Data = TOF_GetDistance(&sensor1);
    HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, 0);

    // snprintf(buff, 500, "Sensor0 measurments: %d,\nSensor1 measurments: %d\n\n", sensor0_Data, sensor1_Data);
    // HAL_UART_Transmit(&huart2, buff, 500, 1000);
    // memset(buff, 0, 500);

    LOG_EVENT("\n   Sensor0 measurments: %d mm,\n   Sensor1 measurments: %d mm\n\n", sensor0_Data, sensor1_Data);
    LOG_EVENT(" TIM2->CCR1 = %d\n", TIM2->CCR1);
    
	  // HAL_Delay(1000);
    for (uint32_t i = TIM2->CCR1; i > 0; i -= 20)
    {
      TIM2->CCR1 = i;
      HAL_Delay(1);
    }
    
    // TIM1->CCR1 = 0;
    HAL_Delay(100);

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_I2C1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_HSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
