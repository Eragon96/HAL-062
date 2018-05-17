/**
  ******************************************************************************
  * @file    Project/STM32F4xx_StdPeriph_Templates/main.c 
  * @author  MCD Application Team
  * @version V1.8.0
  * @date    04-November-2016
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2016 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "USART_lib.h"
#include "PWM_lib.h"
/** @addtogroup Template_Project
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static __IO uint32_t uwTimingDelay;
RCC_ClocksTypeDef RCC_Clocks;

/* Private function prototypes -----------------------------------------------*/
static void Delay(__IO uint32_t nTime);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
RCC_ClocksTypeDef RCC_Clocks;
void SysTick_Handler(void)
{

}
int main(void)	{
		RCC_DeInit();

	    RCC_HSEConfig(RCC_HSE_ON);
	    while(RCC_WaitForHSEStartUp() != SUCCESS);

	    RCC_PLLConfig(RCC_PLLSource_HSE, 4, 140, 2, 4);
	    RCC_HCLKConfig(RCC_SYSCLK_Div1);

	    RCC_PCLK1Config(RCC_HCLK_Div4);
	    RCC_PCLK2Config(RCC_HCLK_Div2);
	    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
	    RCC_PLLCmd(ENABLE);
	    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) != SET);

	    //SysTick initialisation:
	    RCC_GetClocksFreq( &RCC_Clocks);
	    //SysTick_Config(RCC_Clocks.SYSCLK_Frequency/10000);

		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
		//yellow
		GPIO_InitTypeDef GPIO_InitStructure;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_Init(GPIOE, &GPIO_InitStructure);

		//red

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
		GPIO_Init(GPIOB, &GPIO_InitStructure);


		RCC_GetClocksFreq( &RCC_Clocks);

		int i=0;

		usart_Init();
		PWM_Init();
		TIM_SetCompare1(TIM11,1000);
		TIM_SetCompare1(TIM10,1000);
		TIM_SetCompare1(TIM13,1000);





  while (1)
  {

	  //RCC_GetClocksFreq( &RCC_Clocks);
	  //while(!USART_GetFlagStatus(USART2, USART_FLAG_TXE));
	  //
	  //
	 // USART_SendData(USART2, 'a');
  }
}





/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in milliseconds.
  * @retval None
  */
void Delay(__IO uint32_t nTime)
{ 
  uwTimingDelay = nTime;

  while(uwTimingDelay != 0);
}

/**
  * @brief  Decrements the TimingDelay variable.
  * @param  None
  * @retval None
  */
void TimingDelay_Decrement(void)
{
  if (uwTimingDelay != 0x00)
  { 
    uwTimingDelay--;
  }
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
