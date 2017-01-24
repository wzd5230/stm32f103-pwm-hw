/**
  ******************************************************************************
  * @file    main.c
  * @author  wang zheng dong
  * @version none
  * @date    24-Jan-2017
  * @brief   this is a simple example of implementing a pwm by using pwm1 of tim2.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */


/*******************************************************************************
 * Includes.
 */
#include "stm32f10x.h"


/**
  * fun     pwm_io_init
  * param   none
  * retval  none
  * @brief  initialize the gpio of pwm1 of timer2.
  *         using default alternate function of PA.2,or remapping alternate function
  *         of PB.10.
  */
void pwm_io_init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  
#if 0
  /* the default alternate function of PA.2 is TIM2_CH3.
   */
  
  /* enable clock. */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
  
  /* initialize the gpio. */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
#else
  /* the default alternate function of PB.10 is not TIM2_CH3,so we need config the
   * remap alternate function of pb.10.
   */
  
  /* enable clock. */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
  
  /* initialize the gpio. */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
  GPIO_PinRemapConfig(GPIO_FullRemap_TIM2, ENABLE);
  
#endif
  
  
}


/**
  * fun     pwm_timer_init
  * param   none
  * retval  none
  * @brief  initialize the pwm1 of timer2.
  */
void pwm_timer_init(void)
{
  
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
  TIM_OCInitTypeDef TIM_OCInitStructure;
  
  /* enable clock of timer2. */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  
  
  TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;                   /* 72M */
  TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1;                             /* freq = 1MHz */
  TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInitStructure.TIM_Period = 100-1;                                 /* pwm period is 10khz */
  
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
  
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 90;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OC3Init(TIM2, &TIM_OCInitStructure);
  
  
  
  TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);
  TIM_ARRPreloadConfig(TIM2, ENABLE);
  TIM_Cmd(TIM2, ENABLE);
  
}


/**
  * fun     main
  * param   none
  * retval  none
  * @brief
  */
void main(void)
{
  pwm_io_init();
  pwm_timer_init();
  
  while(1)
  {
  }
}