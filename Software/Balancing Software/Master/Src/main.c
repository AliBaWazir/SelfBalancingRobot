/**
  ******************************************************************************
  * File Name          : main.c
  * Date               : 26/10/2014 15:33:52
  * Description        : Main program body
  ******************************************************************************

  */

/* Includes ------------------------------------------------------------------*/
#include "stm32fxxx_hal.h"
#include "main.h"
#include "tm_stm32_usart.h"


volatile uint32_t hal_timestamp = 0;




/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

struct hal_s hal = {0};

volatile unsigned char rx_new;

unsigned char *mpl_key = (unsigned char*)"eMPL 5.1";

struct platform_data_s {
	signed char orientation[9];
};

static struct platform_data_s gyro_pdata = {
    .orientation = {  1, 0, 0,
                      0, 1, 0,
                      0, 0, 1}
};

#if defined MPU9150 || defined MPU9250
static struct platform_data_s compass_pdata = {
    .orientation = { 0, 1, 0,
                     1, 0, 0,
                     0, 0, -1}
};
#define COMPASS_ENABLED 1
#elif defined AK8975_SECONDARY
static struct platform_data_s compass_pdata = {
    .orientation = {-1, 0, 0,
                     0, 1, 0,
                     0, 0,-1}
};
#define COMPASS_ENABLED 1
#elif defined AK8963_SECONDARY
static struct platform_data_s compass_pdata = {
    .orientation = {-1, 0, 0,
                     0,-1, 0,
                     0, 0, 1}
};
#define COMPASS_ENABLED 1
#endif

enum packet_type_e {
    PACKET_TYPE_ACCEL,
    PACKET_TYPE_GYRO,
    PACKET_TYPE_QUAT,
    PACKET_TYPE_TAP,
    PACKET_TYPE_ANDROID_ORIENT,
    PACKET_TYPE_PEDO,
    PACKET_TYPE_MISC,
    PACKET_TYPE_COMPASS,
};
extern void userLoop(void);
/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void Board_Init (void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_IRQ_Init (void);
static void Error_Handler (void);


static void read_from_mpl(void)
{
	long msg, data[9];
	int8_t accuracy;
	unsigned long timestamp;
	float float_data[3] = {0};

	if (inv_get_sensor_type_quat(data, &accuracy, (inv_time_t*)&timestamp))
	{
	 /* Sends a quaternion packet to the PC. Since this is used by the Python
		* test app to visually represent a 3D quaternion, it's sent each time
		* the MPL has new data.
		*/
		eMPL_send_quat(data);
        //eMPL_send_data(PACKET_DATA_EULER, data);
        //eMPL_send_data(PACKET_DATA_ROT, data);
        
		/* Specific data packets can be sent or suppressed using USB commands. */
		if (hal.report & PRINT_QUAT)
			eMPL_send_data(PACKET_DATA_QUAT, data);
	}

	if (hal.report & PRINT_ACCEL)
	{
		if (inv_get_sensor_type_accel(data, &accuracy, (inv_time_t*)&timestamp))
			eMPL_send_data(PACKET_DATA_ACCEL, data);
	}
	if (hal.report & PRINT_GYRO)
	{
		if (inv_get_sensor_type_gyro(data, &accuracy, (inv_time_t*)&timestamp))
			eMPL_send_data(PACKET_DATA_GYRO, data);
	}
#ifdef COMPASS_ENABLED
	if (hal.report & PRINT_COMPASS)
	{
		if (inv_get_sensor_type_compass(data, &accuracy, (inv_time_t*)&timestamp))
			eMPL_send_data(PACKET_DATA_COMPASS, data);
	}
#endif
	if (hal.report & PRINT_EULER)
	{
		if (inv_get_sensor_type_euler(data, &accuracy, (inv_time_t*)&timestamp))
			eMPL_send_data(PACKET_DATA_EULER, data);
	}
	if (hal.report & PRINT_ROT_MAT)
	{
		if (inv_get_sensor_type_rot_mat(data, &accuracy, (inv_time_t*)&timestamp))
			eMPL_send_data(PACKET_DATA_ROT, data);
	}
	if (hal.report & PRINT_HEADING)
	{
		if (inv_get_sensor_type_heading(data, &accuracy, (inv_time_t*)&timestamp))
			eMPL_send_data(PACKET_DATA_HEADING, data);
	}
	if (hal.report & PRINT_LINEAR_ACCEL)
	{
		if (inv_get_sensor_type_linear_acceleration(float_data, &accuracy, (inv_time_t*)&timestamp))
		{
			MPL_LOGI("Linear Accel: %7.5f %7.5f %7.5f\r\n",	float_data[0], float_data[1], float_data[2]);                                        
		}
	}
	if (hal.report & PRINT_PEDO)
	{
		unsigned long timestamp;
		timestamp = HAL_GetTick();
		
		if (timestamp > hal.next_pedo_ms)
		{
			hal.next_pedo_ms = timestamp + PEDO_READ_MS;
			unsigned long step_count, walk_time;
			dmp_get_pedometer_step_count(&step_count);
			dmp_get_pedometer_walk_time(&walk_time);
			MPL_LOGI("Walked %ld steps over %ld milliseconds..\n", step_count, walk_time);
		}
	}

	/* Whenever the MPL detects a change in motion state, the application can
	 * be notified. For this example, we use an LED to represent the current
	 * motion state.
	 */
	msg = inv_get_message_level_0(INV_MSG_MOTION_EVENT | INV_MSG_NO_MOTION_EVENT);
	if (msg)
	{
		if (msg & INV_MSG_MOTION_EVENT)
		{
			MPL_LOGI("Motion!\n");
		}
		else if (msg & INV_MSG_NO_MOTION_EVENT)
		{
			MPL_LOGI("No motion!\n");
		}
	}
}


#ifdef COMPASS_ENABLED
void send_status_compass()
{
	long data[3] = { 0 };
	int8_t accuracy = { 0 };
	unsigned long timestamp;
	
	inv_get_compass_set(data, &accuracy, (inv_time_t*) &timestamp);
	MPL_LOGI("Compass: %7.4f %7.4f %7.4f ", data[0]/65536.f, data[1]/65536.f, data[2]/65536.f);
	MPL_LOGI("Accuracy= %d\r\n", accuracy);
}
#endif




void Board_Init (void)
{
	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  //HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();
 
  setup();
  /* System interrupt init*/
  /* Sets the priority grouping field */
  HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_0);
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USB_DEVICE_Init();
  MX_I2C1_Init();
  
}


int main(void)
{
    
	inv_error_t result;
	struct int_param_s int_param;
	
	unsigned char accel_fsr, new_temp = 0, new_compass = 0;
	unsigned short gyro_rate, gyro_fsr, compass_fsr;
	unsigned long timestamp;
	
	int_param.cb = NULL;
	
	Board_Init();
	
	result = mpu_init(&int_param);
  if (result)
	{
		Error_Handler();
  }
	
	result = inv_init_mpl();
  if (result)
	{
		Error_Handler();
  }
	
	inv_enable_quaternion();
	inv_enable_9x_sensor_fusion();
  inv_enable_fast_nomot();
  inv_enable_gyro_tc();
	inv_enable_vector_compass_cal();
	inv_enable_magnetic_disturbance();
	inv_enable_eMPL_outputs();
	
	result = inv_start_mpl();
	if (result == INV_ERROR_NOT_AUTHORIZED)
	{
		Error_Handler();
	}
	if (result)
	{
		Error_Handler();
	}
	
	mpu_set_sensors(INV_XYZ_GYRO | INV_XYZ_ACCEL | INV_XYZ_COMPASS);
	mpu_configure_fifo(INV_XYZ_GYRO | INV_XYZ_ACCEL);
	mpu_set_sample_rate(DEFAULT_MPU_HZ);
	mpu_set_compass_sample_rate(1000 / COMPASS_READ_MS);
	
	mpu_get_sample_rate(&gyro_rate);
  mpu_get_gyro_fsr(&gyro_fsr);
  mpu_get_accel_fsr(&accel_fsr);
  mpu_get_compass_fsr(&compass_fsr);
	
	inv_set_gyro_sample_rate(1000000L / gyro_rate);
	inv_set_accel_sample_rate(1000000L / gyro_rate);
  inv_set_compass_sample_rate(COMPASS_READ_MS * 1000L);
	
	
	inv_set_gyro_orientation_and_scale(
		  inv_orientation_matrix_to_scalar(gyro_pdata.orientation),
			(long)gyro_fsr<<15);
	inv_set_accel_orientation_and_scale(
		  inv_orientation_matrix_to_scalar(gyro_pdata.orientation),
			(long)accel_fsr<<15);
	inv_set_compass_orientation_and_scale(
			inv_orientation_matrix_to_scalar(compass_pdata.orientation),
			(long)compass_fsr<<15);
			
  hal.sensors = ACCEL_ON | GYRO_ON | COMPASS_ON;
	hal.dmp_on = 0;
	hal.report = 0;
	hal.next_pedo_ms = 0;
	hal.next_compass_ms = 0;
	hal.next_temp_ms = 0;
	
	timestamp = HAL_GetTick();
	
	dmp_load_motion_driver_firmware();
	dmp_set_orientation(
			inv_orientation_matrix_to_scalar(gyro_pdata.orientation));
	
	hal.dmp_features = DMP_FEATURE_6X_LP_QUAT | DMP_FEATURE_TAP |
											DMP_FEATURE_ANDROID_ORIENT | DMP_FEATURE_SEND_RAW_ACCEL | 
											DMP_FEATURE_SEND_CAL_GYRO |	DMP_FEATURE_GYRO_CAL;
	dmp_enable_feature(hal.dmp_features);
	dmp_set_fifo_rate(DEFAULT_MPU_HZ);
	mpu_set_dmp_state(1);
	
	hal.dmp_on = 1;
	
	MX_IRQ_Init();
	
  /* Infinite loop */
  while (1)
  {
    userLoop();
    unsigned long sensor_timestamp;
    int new_data = 0;
		
		timestamp = HAL_GetTick();
		
		if ((timestamp > hal.next_compass_ms) && !hal.lp_accel_mode && hal.new_gyro && (hal.sensors & COMPASS_ON))
		{
			hal.next_compass_ms = timestamp + COMPASS_READ_MS;
			new_compass = 1;
        }
		
		if (timestamp > hal.next_temp_ms) 
		{
            hal.next_temp_ms = timestamp + TEMP_READ_MS;
            new_temp = 1;
        }
		
		if (hal.motion_int_mode)
		{
			/* Enable motion interrupt. */
			mpu_lp_motion_interrupt(500, 1, 5);
			/* Notify the MPL that contiguity was broken. */
			inv_accel_was_turned_off();
			inv_gyro_was_turned_off();
			inv_compass_was_turned_off();
			inv_quaternion_sensor_was_turned_off();
			/* Wait for the MPU interrupt. */
			while (!hal.new_gyro) {}
			/* Restore the previous sensor configuration. */
			mpu_lp_motion_interrupt(0, 0, 0);
			hal.motion_int_mode = 0;
        }
		
		if (!hal.sensors || !hal.new_gyro)
		{
            continue;
        }    
		
		if (hal.new_gyro && hal.dmp_on)
		{
            
			short gyro[3], accel_short[3], sensors;
			unsigned char more;
			long accel[3], quat[4], temperature;
            //about to read fifo
			
            
           
            dmp_read_fifo(gyro, accel_short, quat, &sensor_timestamp, &sensors, &more);\
//            for(int i = more; i > 0;i--){
//                HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, GPIO_PIN_SET);
//                //HAL_Delay(1);
//                HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, GPIO_PIN_RESET);
//                //HAL_Delay(1);
//                
//            }
            
			if (!more)hal.new_gyro = 0;
             
			
			if (sensors & INV_XYZ_GYRO)
			{
				/* Push the new data to the MPL. */
				inv_build_gyro(gyro, sensor_timestamp);
				new_data = 1;
				if (new_temp)
				{
					new_temp = 0;
					/* Temperature only used for gyro temp comp. */
					mpu_get_temperature(&temperature, &sensor_timestamp);
					inv_build_temp(temperature, sensor_timestamp);
				}
			}
			if (sensors & INV_XYZ_ACCEL)
			{
					accel[0] = (long)accel_short[0];
					accel[1] = (long)accel_short[1];
					accel[2] = (long)accel_short[2];
					inv_build_accel(accel, 0, sensor_timestamp);
					new_data = 1;
			}
			if (sensors & INV_WXYZ_QUAT)
			{
					inv_build_quat(quat, 0, sensor_timestamp);
					new_data = 1;
			}
            
            
		}
        
//		else if (hal.new_gyro)
//		{			
//			short gyro[3], accel_short[3];
//			unsigned char sensors, more;
//			long accel[3], temperature;
//			
//			hal.new_gyro = 0;
//			mpu_read_fifo(gyro, accel_short, &sensor_timestamp, &sensors, &more);
//			if (more)
//				hal.new_gyro = 1;
//			if (sensors & INV_XYZ_GYRO)
//			{
//				/* Push the new data to the MPL. */
//				inv_build_gyro(gyro, sensor_timestamp);
//				new_data = 1;
//				if (new_temp)
//				{
//					new_temp = 0;
//					/* Temperature only used for gyro temp comp. */
//					mpu_get_temperature(&temperature, &sensor_timestamp);
//					inv_build_temp(temperature, sensor_timestamp);
//				}
//			}
//			if (sensors & INV_XYZ_ACCEL)
//			{
//				accel[0] = (long)accel_short[0];
//				accel[1] = (long)accel_short[1];
//				accel[2] = (long)accel_short[2];
//				inv_build_accel(accel, 0, sensor_timestamp);
//				new_data = 1;
//			}
//		}
		
		if (new_compass)
		{
			short compass_short[3];
			long compass[3];
			new_compass = 0;
			/* For any MPU device with an AKM on the auxiliary I2C bus, the raw
			 * magnetometer registers are copied to special gyro registers.
			 */
			if (!mpu_get_compass_reg(compass_short, &sensor_timestamp))
			{
				compass[0] = (long)compass_short[0];
				compass[1] = (long)compass_short[1];
				compass[2] = (long)compass_short[2];
				/* NOTE: If using a third-party compass calibration library,
				 * pass in the compass data in uT * 2^16 and set the second
				 * parameter to INV_CALIBRATED | acc, where acc is the
				 * accuracy from 0 to 3.
				 */
				inv_build_compass(compass, 0, sensor_timestamp);
			}
			new_data = 1;
    }
		
		if (new_data)
		{
			inv_execute_on_data();
			/* This function reads bias-compensated sensor data and sensor
			 * fusion outputs from the MPL. The outputs are formatted as seen
			 * in eMPL_outputs.c. This function only needs to be called at the
			 * rate requested by the host.
			 */
			if (timestamp > hal.next_data_tx_ms)
			{
				hal.next_data_tx_ms += DATA_TX_MS;
				read_from_mpl();
			}
    }
  }
}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_OscInitTypeDef RCC_OscInitStruct;

  __PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_PCLK1
                              |RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);

}

/* I2C1 init function */
#ifdef DISCOVERSION
void MX_IRQ_Init (void)
{
	GPIO_InitTypeDef GPIO_IS;
	
	__GPIOB_CLK_ENABLE();

	GPIO_IS.Pin = GPIO_PIN_4;
	GPIO_IS.Mode = GPIO_MODE_IT_RISING;
	GPIO_IS.Speed = GPIO_SPEED_MEDIUM;
	HAL_GPIO_Init(GPIOB, &GPIO_IS);
	
  HAL_NVIC_SetPriority (EXTI4_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ (EXTI4_IRQn);
}
void MX_I2C1_Init(void)
{

  hi2c1.Instance = I2C3;
  hi2c1.Init.ClockSpeed = 400000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_16_9;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLED;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLED;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLED;
  HAL_I2C_Init(&hi2c1);

}
void MX_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_IS;

  /* GPIO Ports Clock Enable */
    __GPIOH_CLK_ENABLE();
    __GPIOA_CLK_ENABLE();
    __GPIOB_CLK_ENABLE();
    __GPIOC_CLK_ENABLE();
    __GPIOD_CLK_ENABLE();
	
    GPIO_IS.Pin = GPIO_PIN_12|GPIO_PIN_4;
    GPIO_IS.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_IS.Pull = GPIO_NOPULL;
    GPIO_IS.Speed = GPIO_SPEED_FAST;
    HAL_GPIO_Init(GPIOD, &GPIO_IS);
    
    
    

}
#endif
#ifdef PCBVERSION
void MX_IRQ_Init (void){
    __GPIOB_CLK_DISABLE();
	GPIO_InitTypeDef GPIO_IS;
	
	__GPIOB_CLK_ENABLE();

	GPIO_IS.Pin = GPIO_Pin_5;
	GPIO_IS.Mode = GPIO_MODE_IT_RISING;
	GPIO_IS.Speed = GPIO_SPEED_MEDIUM;
	HAL_GPIO_Init(GPIOB, &GPIO_IS);
	
    HAL_NVIC_SetPriority (EXTI9_5_IRQn , 1, 0);
    HAL_NVIC_EnableIRQ (EXTI9_5_IRQn);
}
void MX_GPIO_Init(void)
{
	//GPIO_InitTypeDef GPIO_IS;

  /* GPIO Ports Clock Enable */
    __GPIOA_CLK_ENABLE();
    __GPIOB_CLK_ENABLE();
    __GPIOC_CLK_ENABLE();
    __GPIOD_CLK_ENABLE();
	
    /*
    GPIO_IS.Pin = GPIO_PIN_12|GPIO_PIN_4;
    GPIO_IS.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_IS.Pull = GPIO_NOPULL;
    GPIO_IS.Speed = GPIO_SPEED_FAST;
    HAL_GPIO_Init(GPIOD, &GPIO_IS);
    
    */
    

}
void MX_I2C1_Init(void)
{

  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 400000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_16_9;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLED;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLED;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLED;
  //HAL_I2C_DeInit(&hi2c1);
  HAL_I2C_Init(&hi2c1);

}
#endif
/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/






void Error_Handler (void)
{
	while (1)
		;
}


#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

