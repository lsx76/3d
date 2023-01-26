/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include<stdio.h>
#include "wheel_config.h"
#include "usmart.h"
#include "wheel_encode.h"
#include "wheel_task.h"
#include "wheel.h"
#include "bar.h"
#include "imu.h"
#include "imu_task.h" 
#include "time_delay.h"
#include "track_task.h"
#include "m294.h"
#include "snow.h"
#include "journey.h"
#include "turn_task.h"
#include "lsc.h"
#include "openmv.h"
#include "stack_transfer.h"
#include "qrcode.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */


 /* 初始化四个电机并使能*/
  extern motor_t motor1;
  extern motor_t motor2;
  extern motor_t motor3;
  extern motor_t motor4;
	
	extern ATTITUDE_t  attitude;
	
	extern pid_data_t imu_pid_data;

  //motor_t motor1;
  //motor_t motor2;
  //motor_t motor3;
  //motor_t motor4;


/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
uint8_t Buffer;
uint8_t M294_Rx_buffer;
uint8_t qrcode_Rx_buffer;
uint8_t openmv_Rx_buffer;
extern int encoder;
extern double motor_target[5];
extern pid_data_t motor1_pid_data;
extern pid_data_t motor2_pid_data;
extern pid_data_t motor3_pid_data;
extern pid_data_t motor4_pid_data;
extern pid_data_t track_pid_data;
extern TRACKINGBOARD_t row_bar;
extern TRACKINGBOARD_t vertical_bar;
extern Steering_t turnover_steering;
extern uint8_t putBallOrder[9];


/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

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
  MX_TIM1_Init();
  MX_TIM3_Init();
  MX_TIM2_Init();
  MX_TIM5_Init();
  MX_TIM6_Init();
  MX_USART1_UART_Init();
  MX_TIM8_Init();
  MX_UART5_Init();
  MX_USART6_UART_Init();
  MX_UART8_Init();
  MX_UART7_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */
	HAL_UART_Receive_IT(&huart1,&Buffer,1);
	usmart_dev.init(108); 		    //初始化USMART
	
	HAL_UART_Receive_IT(&huart6,&M294_Rx_buffer, 1);
	HAL_UART_Receive_IT(&huart7,&qrcode_Rx_buffer, 1);

	HAL_UART_Receive_IT(&huart3,OPENMV_Rx_BUF,5);   //串口测试
	
	motor1_Enable(&motor1);
  motor2_Enable(&motor2);
  motor3_Enable(&motor3);
  motor4_Enable(&motor4);
	imu_pid_data_init(&imu_pid_data);
	motor_pid_data_init( &motor1_pid_data); 
	motor_pid_data_init(&motor2_pid_data);
  motor_pid_data_init(&motor3_pid_data);
  motor_pid_data_init(&motor4_pid_data);
	track_pid_data_init(&track_pid_data);
	receive_imu901_Init(&attitude);//这里使能了串口5中断	`
	Steering_Init(&turnover_steering);
	delay_init();
 
//	set_track_status(&row_bar,true);
//	set_track_status(&vertical_bar,true);
	
	
	HAL_TIM_Base_Start_IT(&htim6);//调轮子pid时注释掉
//	
	imu_calibration();
	delay_ms(1000);
	set_imu_status(&attitude,true);
	
	

  /* USER CODE END 2 */

  /* Infinite loop */
	/* USER CODE BEGIN WHILE */
//	cmd_action_group_run(0x00,1);
//	delay_ms(1500);
//	span_find_zero();
//	span(0);
//	set_chassis_speed(120,0,0); 
//	delay_ms(1200);
//	set_chassis_speed(0,0,0);
//	delay_ms(100);
//	move_by_encoder(2,-8500);
//	hit_bar_blue();
//	move_to_bar_left_blue();
//	
//	Catch_Steppedplatform_blue();
//	hit_bar_blue();
//	
//	delay_ms(300);
//	set_chassis_speed(0,0,0);
//	delay_ms(300);
//	set_chassis_speed(-80,0,0);
//	delay_ms(800);
//	set_chassis_speed(0,0,0);
//	delay_ms(300);
//	set_imu_status(&attitude,true);
//	delay_ms(500);
//		
//		set_chassis_speed(0,-150,0);
//		delay_ms(3270);
//		while(1)
//		{
//			set_chassis_speed(-50,0,0);
//			if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_2) == 0||HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_3) == 0)break;
//		}
//		set_chassis_speed(0,0,0);
//		delay_ms(100);
//		set_chassis_speed(0,90,0);
//		delay_ms(800);
//		set_chassis_speed(0,0,0);
//		delay_ms(100);
//		set_chassis_speed(-150,0,0);
//		delay_ms(1500);
//		delay_ms(100);
//		set_chassis_speed(0,-90,0);
//		delay_ms(1000);
//		set_imu_status(&attitude,false);
//		set_chassis_speed(0,0,80);
//		delay_ms(1800);
//		hit_bar_blue();
//		move_to_bar_left_blue();
//		set_chassis_speed(0,0,0);
//		delay_ms(500);
//		set_chassis_speed(20,50,0);
//		delay_ms(650);
//		set_chassis_speed(0,0,0);
//		final_Catch_disc_blue();
//		cmd_action_group_run(0x00,1);
//		delay_ms(1500);
//		set_chassis_speed(50,0,0);
//		delay_ms(500);
//		imu_calibration();
//		delay_ms(500);
//		set_chassis_speed(-50,0,0);
//		delay_ms(1050);
//		set_imu_status(&attitude,true);
//		set_chassis_speed(0,0,0);
//		delay_ms(500);
//		move_by_encoder(2,-5000);
//		while(1)
//		{
//			set_chassis_speed(0,-80,0);
//			if((HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_5) == 0&&HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_7) == 0))break;
//		}
//		set_chassis_speed(0,-80,0);
//		HAL_Delay(1000);
//		hit_bar_blue();
//		move_to_bar_left_blue();
//		distinguish_blue();
//		distinguish_blue();
//		distinguish_blue();
//		distinguish_blue();
//		distinguish_blue();
//		stack_transfer_blue();
////		while(1) 
////	{
////       set_chassis_speed(10, 30, 0);
////       if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_5) == 1&&HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_7) == 0) break;
////  }
//		get_qrcode();
////		get_scores_blue();
//		get_scores_qrcode_blue();
//		
//		set_chassis_speed(-50,0,0);
//		delay_ms(850);
//		set_imu_status(&attitude,true);
//		set_chassis_speed(0,0,0);
//		delay_ms(500);
//		while(1)
//		{
//			set_chassis_speed(0,-80,0);
//			if((HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_5) == 1&&HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_7) == 1))break;
//		}
//		set_chassis_speed(0,-80,0);
//		HAL_Delay(1500);
//		set_chassis_speed(0,-120,0);
//		HAL_Delay(1650);
//		set_chassis_speed(0,0,0);
//		delay_ms(300);
//		set_chassis_speed(-80,0,0);
//		delay_ms(1500);
//	rode_blue_test();
	span_init();
	blue_or_red();

//		distinguish_red();
//		distinguish_red();
//		rode_red_test();
//		set_chassis_speed(0,0,0);
//		delay_ms(300);
//		set_imu_status(&attitude,false);
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
//			set_motor_speed(1,0);
//		printf("%f , %f \n",motor1_pid_data.feedback,motor1_pid_data.expect);//调轮子pid
//		motor_pid();//调轮子pid
		
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 216;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
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
