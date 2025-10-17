
#include "main.h"
#include "i2c.h"
#include "usart.h"
#include "gpio.h"

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

int __io_putchar(int ch)
{
HAL_UART_Transmit(&hlpuart1, (uint8_t *)&ch, 1, 10);
return ch;
}
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
  MX_LPUART1_UART_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  ///* Infinite loop */
  uint8_t who_am_i_a;
  HAL_I2C_Mem_Read(&hi2c1, (0x19 << 1), // Device address
		  	  	  0x0F, // WHO_AM_I register
				  I2C_MEMADD_SIZE_8BIT, // 1-byte register address
				  &who_am_i_a, // Output buffer
				  1, // Number of bytes
				  HAL_MAX_DELAY); // Timeout

  	  	  	  	  printf("%u\r\n",who_am_i_a);


  uint8_t who_am_i_m;
  HAL_I2C_Mem_Read(&hi2c1, (0x1E << 1) , 0x4F, I2C_MEMADD_SIZE_8BIT, &who_am_i_m, 1, HAL_MAX_DELAY);
  printf("%u\r\n", who_am_i_m);


  // Set ctrl1 reg to 50 hz
  //00110111
  uint8_t ctrl1 = 0x37;
  HAL_I2C_Mem_Write(&hi2c1, (0x19 << 1), 0x20, I2C_MEMADD_SIZE_8BIT, &ctrl1, 1, HAL_MAX_DELAY);


  while (1)
    {
  uint8_t acx[2];
  HAL_I2C_Mem_Read(&hi2c1, (0x19 << 1), 0xA8  , I2C_MEMADD_SIZE_8BIT, acx, 2, HAL_MAX_DELAY);

  uint8_t acy[2];
    HAL_I2C_Mem_Read(&hi2c1, (0x19 << 1), 0xAA  , I2C_MEMADD_SIZE_8BIT, acy, 2, HAL_MAX_DELAY);

    uint8_t acz[2];
      HAL_I2C_Mem_Read(&hi2c1, (0x19 << 1), 0xAC  , I2C_MEMADD_SIZE_8BIT, acz, 2, HAL_MAX_DELAY);

 int16_t ax = (int16_t)(acx[1] << 8 | acx[0]);
 int16_t ay = (int16_t)(acy[1] << 8 | acy[0]);
 int16_t az = (int16_t)(acz[1] << 8 | acz[0]);
 // need to divide by gravity

 float gx = ax * 0.0000586f;
 float gy = ay * 0.0000586f;
 float gz = az * 0.0000586f;
 // 14912 adn 14972 are both .91G

 printf("x: %d (%.2f G),y: %d (%.2f G),z: %d(%.2f G)\r\n",
        ax,gx, ay,gy, az,gz);
  /* USER CODE BEGIN WHILE */

    /* USER CODE END WHILE */
//	  char msg[] = "Hpppo\r\n";
//	      printf(msg);
//	 	 // HAL_UART_Transmit(&hlpuart1, (uint8_t*)msg, 7, HAL_MAX_DELAY);
//	 	  HAL_Delay(1000);
//    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}
