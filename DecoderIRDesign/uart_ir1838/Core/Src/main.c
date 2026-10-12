/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "CLCD.h"
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

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */
CLCD_Name LCD1;
uint8_t key = 0;
char LCD_send[16];
char status[10];

uint8_t rx_data;          // D? li?u nh?n 1 byte
uint8_t rx_flag = 0;      // C? b�o d� nh?n du?c d? li?u
float sensor_value = 0;   // Gi� tr? d? li?u thay d?i (v� d? c?m bi?n)
float last_value = 0;     // Luu gi� tr? cu d? so s�nh
char tx_buffer[50];       // B? d?m truy?n UART
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */
#define START_MIN_TIME 130
#define START_MAX_TIME 140
#define COMMAND        17

uint16_t time_pre = 0;
uint16_t time_current = 0;
uint16_t period = 0;
uint8_t count = 0;
uint32_t bit = 0;
uint32_t hex_ir = 0;
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
  MX_USART1_UART_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
	//HAL_UART_Receive_IT(&huart1, &rx_data, 1);
 
	HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_1);
	CLCD_8BIT_Init(&LCD1, 16, 2,CS_GPIO_Port, CS_Pin, EN_GPIO_Port, EN_Pin,
               D0_GPIO_Port, D0_Pin, D1_GPIO_Port, D1_Pin,
							 D2_GPIO_Port, D2_Pin, D3_GPIO_Port, D3_Pin,
							 D4_GPIO_Port, D4_Pin, D5_GPIO_Port, D5_Pin,
							 D6_GPIO_Port, D6_Pin, D7_GPIO_Port, D7_Pin);
							 
	HAL_UART_Transmit(&huart1, (uint8_t *)"UART started\r\n", 13, 1000);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		CLCD_SetCursor(&LCD1, 0, 0);
		CLCD_WriteString(&LCD1, "DIEP VAN DU");
		sprintf(LCD_send, "So phim: %d",key);
		if(hex_ir != 0){
			//memset(status, 0, sizeof(status));
		  switch(hex_ir){
		     case 66961470: key = 0; break;
			   case 66888030: key = 1; break;
			   case 66957390: key = 2; break;
         case 66973710: key = 3; break;
			   case 66871710: key = 4; break;
			   case 66936990: key = 5; break;
			   case 66904350: key = 6; break;
			   case 66847230: key = 7; break;
			   case 66969630: key = 8; break;
			   case 66924750: key = 9; break;
			   default: key = 0; break;
		}	
		   CLCD_SetCursor(&LCD1, 0, 1);
       //CLCD_WriteString(&LCD1, "                "); // clear line
		   sprintf(LCD_send, "So phim: %d",key);
		   CLCD_SetCursor(&LCD1, 0, 1);
		   CLCD_WriteString(&LCD1, LCD_send);
	//	sprintf(LCD_send, "So phim: %d",key);
	//	CLCD_SetCursor(&LCD1, 8, 1);
	//	CLCD_WriteString(&LCD1, LCD_send);
		//hex_ir = 0; 
  }
  sprintf(tx_buffer, "IR Code: %d \r\n", hex_ir);
  HAL_UART_Transmit(&huart1, (uint8_t *)tx_buffer, strlen(tx_buffer), 1000);
	HAL_Delay(100);
	
	//----------------------------------------------------------------------//
	if(key ==0 ){
	  HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(LED3_GPIO_Port,LED3_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(LED4_GPIO_Port,LED4_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(LED5_GPIO_Port,LED5_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(LED6_GPIO_Port,LED6_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(LED7_GPIO_Port,LED7_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(LED8_GPIO_Port,LED8_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(LED9_GPIO_Port,LED9_Pin,GPIO_PIN_SET);
		HAL_Delay(100);
 }
 else{
	 if(key ==1){
		 HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);
	   HAL_Delay(100);
	 }
	 if(key ==2){
		 HAL_GPIO_TogglePin(LED2_GPIO_Port,LED2_Pin);
	   HAL_Delay(100);
	 }
	 if(key ==3){
		 HAL_GPIO_TogglePin(LED3_GPIO_Port,LED3_Pin);
	   HAL_Delay(100);
	 }
	 if(key ==4){
		 HAL_GPIO_TogglePin(LED4_GPIO_Port,LED4_Pin);
	   HAL_Delay(100);
	 }
	 if(key ==5){
		 HAL_GPIO_TogglePin(LED5_GPIO_Port,LED5_Pin);
	   HAL_Delay(100);
	 }
	 if(key ==6){
		 HAL_GPIO_TogglePin(LED6_GPIO_Port,LED6_Pin);
	   HAL_Delay(100);
	 }
	 if(key ==7){
		 HAL_GPIO_TogglePin(LED7_GPIO_Port,LED7_Pin);
	   HAL_Delay(100);
	 }
	 if(key ==8){
		 HAL_GPIO_TogglePin(LED8_GPIO_Port,LED8_Pin);
	   HAL_Delay(100);
	 }
	 if(key ==9){
		 HAL_GPIO_TogglePin(LED9_GPIO_Port,LED9_Pin);
	   HAL_Delay(100);
	 }
 }
}
	//-----------------------------------------------------------------------//
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_IC_InitTypeDef sConfigIC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 799;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 65535;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_IC_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_FALLING;
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 0;
  if (HAL_TIM_IC_ConfigChannel(&htim2, &sConfigIC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, D1_Pin|D2_Pin|D3_Pin|D4_Pin
                          |D5_Pin|D6_Pin|D7_Pin|LED1_Pin
                          |LED2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, D0_Pin|CS_Pin|EN_Pin|LED3_Pin
                          |LED4_Pin|LED5_Pin|LED6_Pin|LED7_Pin
                          |LED8_Pin|LED9_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : D1_Pin D2_Pin D3_Pin D4_Pin
                           D5_Pin D6_Pin D7_Pin LED1_Pin
                           LED2_Pin */
  GPIO_InitStruct.Pin = D1_Pin|D2_Pin|D3_Pin|D4_Pin
                          |D5_Pin|D6_Pin|D7_Pin|LED1_Pin
                          |LED2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : D0_Pin CS_Pin EN_Pin LED3_Pin
                           LED4_Pin LED5_Pin LED6_Pin LED7_Pin
                           LED8_Pin LED9_Pin */
  GPIO_InitStruct.Pin = D0_Pin|CS_Pin|EN_Pin|LED3_Pin
                          |LED4_Pin|LED5_Pin|LED6_Pin|LED7_Pin
                          |LED8_Pin|LED9_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim){
  time_current = HAL_TIM_ReadCapturedValue(&htim2, TIM_CHANNEL_1);
	period = time_current - time_pre;
	time_pre = time_current;
	if(period > START_MIN_TIME && period < START_MAX_TIME){
	  hex_ir = 0;
		count = 0;
		bit = 0;
	}
	else if(period > COMMAND){
	  bit = bit | 0x01;
		bit = bit << 1;
		count++;
	}
	else if(period < COMMAND){
	  bit = bit << 1;
		count++;
	}
	if(count == 32){
	  hex_ir =  bit;
	}
}

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
#ifdef USE_FULL_ASSERT
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
