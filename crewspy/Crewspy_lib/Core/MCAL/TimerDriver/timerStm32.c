/*______________________INCLUDES________________________________*/
#include "timerStm32.h"

/*______________________PRIVATES VARIABLES_______________________*/
PRIVATE timersInfo_t timerInfo;
/*________________________________APIs_______________________*/
apisTmrRetType_t    enum_TIMxInit   (const TimerX_Config_t* strTimerConfigX)
{

    //enable clock to TIMx (x = 1 || 2 || 3 || 4) 
    if(strTimerConfigX->TIMx == TIM1)
    {
        RCC->APB2ENR |= (RCC_APB2ENR_TIM1EN);  //TIMER1
    }   
    else if(strTimerConfigX->TIMx == TIM2)
    {
        RCC->APB1ENR |= (RCC_APB1ENR_TIM2EN); // TIMER2
    }
    else if(strTimerConfigX->TIMx == TIM3)
    {
        RCC->APB1ENR |= (RCC_APB1ENR_TIM3EN); // TIMER3
    }
     else if(strTimerConfigX->TIMx == TIM4)
    {
        RCC->APB1ENR |= (RCC_APB1ENR_TIM4EN); // TIMER4
    }

     else 
    {
        return returnError ;
    }
   
         
    //  Up MODE  or   DOWN  MODE
    if(strTimerConfigX->CounterMode==DOWN_CNT)
    {
        strTimerConfigX->TIMx->CR1 &= ~(TIM_CR1_CMS_Msk);
        strTimerConfigX->TIMx->CR1 |= (TIM_CR1_DIR_Msk);
    }
    else if(strTimerConfigX->CounterMode==UP_CNT)
    {
        strTimerConfigX->TIMx->CR1 &= ~(TIM_CR1_CMS_Msk) ;
        strTimerConfigX->TIMx->CR1 &= ~(TIM_CR1_DIR_Msk) ;    
    }
    else 
    {
        return returnError;
    }

   

    //period
    strTimerConfigX->TIMx->ARR = (strTimerConfigX->OverFolwPeriod) +1;

    //prescaler 
	strTimerConfigX->TIMx->PSC = (strTimerConfigX->Prescaler)+1 ;


     // Enable Timerx interrupt 
    if((strTimerConfigX->UpdateInterruptEnable == TMRX_IRQ_EN) && ( strTimerConfigX->TIMx == TIM1 )  )
    {
        strTimerConfigX->TIMx->CR1 |= (TIM_CR1_URS_Msk);
        strTimerConfigX->TIMx->CR1 &= ~(TIM_CR1_UDIS_Msk);
        strTimerConfigX->TIMx->CR1 |= (TIM_CR1_ARPE_Msk);
        strTimerConfigX->TIMx->DIER |= (TIM_DIER_UIE_Msk);
        NVIC_EnableIRQ(TIM1_UP_IRQn);
    }
    else if((strTimerConfigX->UpdateInterruptEnable == TMRX_IRQ_EN) && ( strTimerConfigX->TIMx == TIM2 )  )
    {
        strTimerConfigX->TIMx->CR1 |= (TIM_CR1_URS_Msk);
        strTimerConfigX->TIMx->CR1 &= ~(TIM_CR1_UDIS_Msk);
        strTimerConfigX->TIMx->CR1 |= (TIM_CR1_ARPE_Msk);
        strTimerConfigX->TIMx->DIER |= (TIM_DIER_UIE_Msk);
        NVIC_EnableIRQ(TIM2_IRQn);
    }
    else if((strTimerConfigX->UpdateInterruptEnable == TMRX_IRQ_EN) && ( strTimerConfigX->TIMx == TIM3 )  )
    {
        strTimerConfigX->TIMx->CR1 |= (TIM_CR1_URS_Msk);
        strTimerConfigX->TIMx->CR1 &= ~(TIM_CR1_UDIS_Msk);
        strTimerConfigX->TIMx->CR1 |= (TIM_CR1_ARPE_Msk);
        strTimerConfigX->TIMx->DIER |= (TIM_DIER_UIE_Msk);
        NVIC_EnableIRQ(TIM3_IRQn);
    }
    else if((strTimerConfigX->UpdateInterruptEnable == TMRX_IRQ_EN) && ( strTimerConfigX->TIMx == TIM4 )  )
    {
        strTimerConfigX->TIMx->CR1 |= (TIM_CR1_URS_Msk);
        strTimerConfigX->TIMx->CR1 &= ~(TIM_CR1_UDIS_Msk);
        strTimerConfigX->TIMx->CR1 |= (TIM_CR1_ARPE_Msk);
        strTimerConfigX->TIMx->DIER |= (TIM_DIER_UIE_Msk);
        NVIC_EnableIRQ(TIM4_IRQn);
    }
    else 
    {
        /*MISRA*/
    }


    //initialization is DONE successfuly, save timer period in static variable 
    
    if(strTimerConfigX->TIMx == TIM1)
    {
        //TIMER1
        timerInfo.initDone[TIMER1]=DONE;
        timerInfo.period[TIMER1] = TIM1->ARR;
    }   
    else if(strTimerConfigX->TIMx == TIM2)
    {
         // TIMER2
         timerInfo.initDone[TIMER2]=DONE;
         timerInfo.period[TIMER2] = TIM2->ARR;
    }
    else if(strTimerConfigX->TIMx == TIM3)
    {
        // TIMER3
        timerInfo.initDone[TIMER3]=DONE;
         timerInfo.period[TIMER3] = TIM3->ARR;
    }
     else if(strTimerConfigX->TIMx == TIM4)
    {
         // TIMER4
         timerInfo.initDone[TIMER4]=DONE;
        timerInfo.period[TIMER4] = TIM4->ARR;
    }

     else 
    {
        return returnError ;
    }

    // Generate an update event to reload the Prescaler value immediately
    strTimerConfigX->TIMx->EGR = TIM_EGR_UG;

    return returnOk;
}

apisTmrRetType_t    enum_TIMxStartCounting          ( TIM_TypeDef* TIMx)
{
     if((TIMx==TIM1) && (timerInfo.initDone[TIMER1]==DONE))
     {
        timerInfo.startDone[TIMER1] = DONE;
     }
     else if((TIMx==TIM2) && (timerInfo.initDone[TIMER2]==DONE))
     {
        timerInfo.startDone[TIMER2] = DONE;
     }
     else if((TIMx==TIM3) && (timerInfo.initDone[TIMER3]==DONE))
     {
        timerInfo.startDone[TIMER3] = DONE;
     }
     else if((TIMx==TIM4) && (timerInfo.initDone[TIMER4]==DONE))
     {
        timerInfo.startDone[TIMER4] = DONE;
     }
     else 
     {
        return returnError;
     }
      
      TIMx->CR1 |= (TIM_CR1_CEN);
      return returnOk;
}
apisTmrRetType_t    enum_TIMxStopCounting           ( TIM_TypeDef* TIMx)
{
    if(
            ((TIMx==TIM1) && (timerInfo.startDone[TIMER1]==DONE)) ||
            ((TIMx==TIM2) && (timerInfo.startDone[TIMER2]==DONE)) ||
            ((TIMx==TIM3) && (timerInfo.startDone[TIMER3]==DONE)) ||
            ((TIMx==TIM4) && (timerInfo.startDone[TIMER4]==DONE))
       )
    {
        //stop TimerX
        TIMx->CR1&= ~(TIM_CR1_CEN);
    }  
    else
    {
         return returnError;
    }
    return returnOk;
}

 
apisTmrRetType_t    enum_TIMxDeInit                 ( TIM_TypeDef* TIMx)
{
    /* DeInit the low level hardware: CLOCK (Peripheral clock stop) , NVIC (Interrupt disable) */
    if(TIMx == TIM1)
    { 
        //TIMER1
        RCC->APB2ENR &= ~(RCC_APB2ENR_TIM1EN); 
        NVIC_DisableIRQ(TIM1_UP_IRQn);
        timerInfo.initDone[TIMER1] = NOT_YET;
        timerInfo.startDone[TIMER1] = NOT_YET;
    }   
    else if(TIMx == TIM2)
    {
        // TIMER2
        RCC->APB1ENR &= ~(RCC_APB1ENR_TIM2EN); 
        NVIC_DisableIRQ(TIM2_IRQn);
        timerInfo.initDone[TIMER2] = NOT_YET;
        timerInfo.startDone[TIMER2] = NOT_YET;
    }
    else if(TIMx == TIM3)
    { 
        // TIMER3
        RCC->APB1ENR &= ~(RCC_APB1ENR_TIM3EN);
        NVIC_DisableIRQ(TIM3_IRQn);
        timerInfo.initDone[TIMER3] = NOT_YET;
        timerInfo.startDone[TIMER3] = NOT_YET;
    }
     else if(TIMx == TIM4)
    {
        // TIMER4
        RCC->APB1ENR &= ~(RCC_APB1ENR_TIM4EN); 
        NVIC_DisableIRQ(TIM4_IRQn);
        timerInfo.initDone[TIMER4] = NOT_YET;
        timerInfo.startDone[TIMER4] = NOT_YET;
    }

     else 
    {
         return returnError;
    }

    return returnOk;
}
uint64_t   u64_GetTIMxCounter             ( TIM_TypeDef* TIMx)
{
     uint64_t LOC_u64TmrxVal = 0x00; 

    if((TIMx==TIM1) && (timerInfo.initDone[TIMER1]==DONE) && (timerInfo.startDone[TIMER1]==DONE))
    {
       // to calculate total counts in all overflows happend
       LOC_u64TmrxVal = timerInfo.overFlow[TIMER1] * timerInfo.period[TIMER1];
       // add the current counts also
       LOC_u64TmrxVal += TIM1->CNT;
       //clear for a new reading
       timerInfo.overFlow[TIMER1]=0;
       TIM1->CNT = 0x00;
    }
    else if((TIMx==TIM2) && (timerInfo.initDone[TIMER2]==DONE) && (timerInfo.startDone[TIMER2]==DONE))
    {
        // to calculate total counts in all overflows happend
       LOC_u64TmrxVal = timerInfo.overFlow[TIMER2] * timerInfo.period[TIMER2];
       // add the current counts also
       LOC_u64TmrxVal += TIM2->CNT;
       //clear for a new reading
       timerInfo.overFlow[TIMER2]=0;
       TIM2->CNT = 0x00;
    }
    else if((TIMx==TIM3) && (timerInfo.initDone[TIMER3]==DONE) && (timerInfo.startDone[TIMER3]==DONE))
    {
         // to calculate total counts in all overflows happend
       LOC_u64TmrxVal = timerInfo.overFlow[TIMER3] * timerInfo.period[TIMER3];
       // add the current counts also
       LOC_u64TmrxVal += TIM3->CNT;
       //clear for a new reading
       timerInfo.overFlow[TIMER3]=0;
       TIM3->CNT = 0x00;
    }
    else if((TIMx==TIM4) && (timerInfo.initDone[TIMER4]==DONE) && (timerInfo.startDone[TIMER4]==DONE))
    {
         // to calculate total counts in all overflows happend
       LOC_u64TmrxVal = timerInfo.overFlow[TIMER4] * timerInfo.period[TIMER4];
       // add the current counts also
       LOC_u64TmrxVal += TIM4->CNT;
       //clear for a new reading
       timerInfo.overFlow[TIMER4]=0;
       TIM4->CNT = 0x00;
    }
    else
    {
        LOC_u64TmrxVal = 0x00;
    }
    return LOC_u64TmrxVal;
}
apisTmrRetType_t    enum_SetTIMxCounter             ( TIM_TypeDef* TIMx, uint16_t u16CounterUpdateVal)
{
    if(
            ((TIMx==TIM1) && (timerInfo.initDone[TIMER1]==DONE)) ||
            ((TIMx==TIM2) && (timerInfo.initDone[TIMER2]==DONE)) ||
            ((TIMx==TIM3) && (timerInfo.initDone[TIMER3]==DONE)) ||
            ((TIMx==TIM4) && (timerInfo.initDone[TIMER4]==DONE))
       )
       {
        TIMx->CNT = u16CounterUpdateVal;
       }
    else 
    {
         return returnError;
    }
    return returnOk;
}




void TIM1_UP_IRQHandler(void)
{
  TIM1->SR &= ~(1U<<0);
  TIM1->CR1 &= ~(TIM_CR1_UDIS_Msk);
  timerInfo.overFlow[TIMER1]++;
  /*
     call your callBack Here if it is desired!
  */
}

void TIM2_IRQHandler(void)
{
  TIM2->SR &= ~(1U<<0);
  TIM2->CR1 &= ~(TIM_CR1_UDIS_Msk);
  timerInfo.overFlow[TIMER2]++;
  /*
     call your callBack Here if it is desired!
  */
}

void TIM3_IRQHandler(void)
{
  TIM3->SR &= ~(1U<<0);
  TIM3->CR1 &= ~(TIM_CR1_UDIS_Msk);
  timerInfo.overFlow[TIMER3]++;
  /*
     call your callBack Here if it is desired!
  */
}

void TIM4_IRQHandler(void)
{
  TIM4->SR &= ~(1U<<0);
  TIM4->CR1 &= ~(TIM_CR1_UDIS_Msk);
  timerInfo.overFlow[TIMER4]++;
  /*
     call your callBack Here if it is desired!
  */
}