#include "stm8s_conf.h"
uint32_t clk;
uint8_t countSetPwm = 0;        //bien nay co tac dung dieu chinh toc do dong co
bool statusStop = TRUE;     //true la he thong dang dung im, false la he thong dang chuyen dong
bool countHall1 = FALSE, countHall2 = FALSE;
bool modeFast = FALSE;
bool Forward = TRUE;    //chieu quay thuan
bool fristRun = TRUE;   //kiem tra lan chay dau tinh khoang cach chieu dai tu
uint8_t countFrirstRun = 0;  //dem so lan va cham
void main( void )
{
  //setup clock 16Mhz
  CLK_DeInit();
  CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);      //f_Master = HSI/1 = 16MHz
  CLK_SYSCLKConfig(CLK_PRESCALER_CPUDIV1);            //f_CPU = f_Master/1 = 16MHz
  while(CLK_GetFlagStatus(CLK_FLAG_HSIRDY)!=SET);
  clk = CLK_GetClockFreq();

  
  GPIO_Init(GPIOC, GPIO_PIN_5, GPIO_MODE_OUT_PP_HIGH_FAST);     //PWM - phat xung toc do
  GPIO_Init(GPIOC, GPIO_PIN_4, GPIO_MODE_OUT_PP_HIGH_FAST);     //FR - chieu quay
  GPIO_Init(GPIOC, GPIO_PIN_3, GPIO_MODE_OUT_PP_HIGH_FAST);     //led test
  GPIO_Init(GPIOB, GPIO_PIN_4, GPIO_MODE_IN_PU_IT);             //hall sensor1
  GPIO_Init(GPIOB, GPIO_PIN_5, GPIO_MODE_IN_PU_IT);             //hall sensor2
  GPIO_Init(GPIOD, GPIO_PIN_3, GPIO_MODE_IN_PU_IT);             //FG - toc do phan hoi ve
  GPIO_Init(GPIOD, GPIO_PIN_2, GPIO_MODE_IN_PU_IT);             //config RF

  disableInterrupts();
  //setup extenal interrupt
  GPIO_Init(GPIOD, GPIO_PIN_4, GPIO_MODE_IN_PU_IT);
  GPIO_Init(GPIOD, GPIO_PIN_5, GPIO_MODE_IN_PU_IT);
  EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOD, EXTI_SENSITIVITY_FALL_ONLY);
  //note PD7 is LTI, use INTERRUPT_HANDLER(LTI_IRQHandler, 0)

  //setup timer2
  TIM2_TimeBaseInit(TIM2_PRESCALER_512,62500);
  //TIM2_TimeBaseInit(TIM2_PRESCALER_1,160);            //tan so la 16MHz
                                                       //ti le chia la 1, vi the 1 chu ky lenh voi 16Mhz la 0.0625us
                                                      //timer 2 dem den 160 thi se ngat tiemr, tuong ung voi 10us
                                                      //timer 2 la 16bit, dem tu 0 den 65535
  //TIM2_ClearFlag(TIM2_IT_UPDATE);                     //xoa thanh ghi co bao ngat
  TIM2_ITConfig(TIM2_IT_UPDATE, ENABLE);              //khoi dong timer2 dem den thanh ghi TIM2_IT_UPDATE
  TIM2_Cmd(ENABLE);
  enableInterrupts();
  while(1){

  }
}


#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
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