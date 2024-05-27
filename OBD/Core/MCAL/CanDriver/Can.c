/**
 * @file Can.c
 * @author  Ahmed Bahaa - (https://crewteq.com/)
 
 * @brief This is the source file for the CAN Driver Component for STM32F103C8T6, Target Device has Only One Can Peripheral 
          File Contains Functions Definitions and Component logic
 * @version 1.6.0
 * @date 2023-10-9
 * 
 * @copyright Copyright (crewteq) 2023 
 */

/*________________________________Dependencies_______________________________*/
#include "Can.h"
#include "CanCnfg.h"


#include "BitMath.h"
#include "stm32f103xb.h"

/*________________________________Macros_______________________________*/

#define MAX_STANDARD_ID_VALUE     2047U            /*Max Value that can be put for a CAN FRAME Standard ID (11 bits)*/
#define MAX_EXTENDED_ID_VALUE     536870911U       /*Max Value that can be put for a CAN FRAME Extended ID (29 bits)*/
#define EXTID_MASK                 
 
#define MAILBOX_EMPTY              1               /*Macro for Checking if MailBox is empty in the CAN_TSR Register */

/*________________________________IRQ Prototypes_______________________________*/
void  USB_LP_CAN1_RX0_IRQHandler(void);               /*RX0 IRQ Handler Prototype*/
void  USB_HP_CAN1_TX_IRQHandler(void);               /*TX0IRQ Handler Prototype*/
void  CAN1_SCE_IRQHandler(void);                     /*error ISR Handler*/

/*________________________________Global Variables_______________________________*/

/// @brief pointer to the CAN Peripheral Structure containing Peripheral's registers
/// @note  Cover Requirement CCO-CDD-1204
PRIVATE CAN_TypeDef *GLOB_strCanChannel;                            

/// @brief Global structure to store the Recieved Frame
/// @note  Cover Requirement CCO-CDD-1203
PRIVATE strCanDrvFrameInfo GLOB_strRxFrame;                        

/// @brief variable to store wake up ID to call Wake up Callback function upon a reception on it
/// @note  Cover Requirement CCO-CDD-1227
PRIVATE u32_t GLOB_WakeUpID;                      


/// @brief Pointer to Call back function upon receiving
/// @note  Cover Requirement CCO-CDD-1206
PRIVATE void(*GLOB_CanDrvReceptionCallback)(void)=NULL;          

/// @brief Pointer to Call back function upon Transmiting
/// @note  Cover Requirement CCO-CDD-1205
PRIVATE  void(*GLOB_CanDrvTransmissionCallback)(void)=NULL;     

/// @brief Pointer to Call back function upon Transmiting
/// @note  Cover Requirement CCO-CDD-1228
PRIVATE  void(*GLOB_CanDrvBusOffErrorCallback)(void)=NULL;     

/// @brief Pointer to Call back function upon receiving a msg on a Specific CAN ID
/// @note  Cover Requirement CCO-CDD-1229
PRIVATE  void(*GLOB_CanDrvWakeUpCallback)(void)=NULL;   

/// @brief Function to make global pointer to functions point to when no callback set is done by upper layers
/// @param  
void EmptyFunction(void);

/*________________________________Functions Implementation_______________________________*/
/*______________________________________________________________________________________________________________*/

void EmptyFunction(void)
{
  /*do nothing*/
}


void vid_CanDrvInit (void)
{
    /*Assign Instance to the CAN1 Channel as it is the only Channel Found in Target Device */
    GLOB_strCanChannel=CAN1;
    
    /*Enable CAN Peripheral Clock and GPIOA Peripheral Clock */
    CREW_SET_BIT(RCC->APB1ENR,RCC_APB1ENR_CAN1EN_Pos);
    CREW_SET_BIT(RCC->APB2ENR,RCC_APB2ENR_IOPAEN_Pos);

    /*Configure GPIOA pin 12 to work as CAN TX alternate Function output (push-pull), with Maximum output speed 10MHZ */
    CREW_CLR_BIT(GPIOA->CRH,18);
    GPIOA->CRH|= (1<<19) | (1<<16);
  
  /*Configure GPIOA pin 11 to work as CAN RX - Input Floating*/
    CREW_SET_BIT(GPIOA->CRH,14);
    CREW_CLR_BIT(GPIOA->CRH,15);

  /*ReMap GPIOA Pin 11 and 12 in the Alternate Function Map register to CAN Peripheral By Clearing These Two Bits*/
    AFIO->MAPR&= ~ ( (1<<AFIO_MAPR_CAN_REMAP_Pos) | ( (1<<AFIO_MAPR_CAN_REMAP_Pos)+1) );

        /*Enbale IRQ in NVIC for CAN_RX,CAN_TXa and Status change error*/
        NVIC_EnableIRQ(USB_LP_CAN1_RX0_IRQn  );
        NVIC_EnableIRQ(CAN1_SCE_IRQn);
        NVIC_EnableIRQ( USB_HP_CAN1_TX_IRQn  );

        /*Enbale the following interrupts in the CAN Interrupt enable register (IER)
        * - FMPIE0: FIFO Recieving Interrupt
          - TMEIE:  Transmit MailBox Empty Interrupt
          - FMPIE0: Recieveing mailbox 0 interrupt
          - BOFIE : Bus off error detection */
        
        GLOB_strCanChannel->IER |=   (1<<CAN_IER_FMPIE0_Pos) | (1<<CAN_IER_ERRIE_Pos)| (1<<CAN_IER_TMEIE_Pos) | (1<<CAN_IER_BOFIE_Pos);
                          


        /*enable global interrupt bit*/
          __enable_irq();



/* Request to exit Sleep mode */
 GLOB_strCanChannel->MCR &= ~ (1<<CAN_MCR_SLEEP_Pos);

  /*Configure CAN Master Control Register (CAN_MCR)*/
  /*INRQ: 1 ----> Initalization Mode
    ABOM: 1 ----> Automatic Bus Off Management On
    NART_:1 ----> No automatic retransmission
    TXFP :1-----> Transmit FIFO priority (Priority driven by the request order chronologically)*/
 GLOB_strCanChannel->MCR |= (1<<CAN_MCR_INRQ_Pos) |  (1<<CAN_MCR_ABOM_Pos) | (1<<CAN_MCR_TXFP_Pos) | (1<<CAN_MCR_NART_Pos) ;



 /* Wait for initialization mode */
  while((CAN_MSR_SLAK == (CAN_MSR_SLAK & CAN1->MSR))
      || (CAN_MSR_INAK != (CAN_MSR_INAK & CAN1->MSR)))
  {
    /* Do nothing until initialization mode is entered */
  }

 /*Configure CAN interrupt enable register(CAN_IER)*/
 /*FMPIE0: 1 ---> FIFO message pending interrupt enable
   ERRIE : 1 ---> Error interrupt enable*/
GLOB_strCanChannel->IER |= (1<<CAN_IER_FMPIE0_Pos) | (1<<CAN_IER_ERRIE_Pos) | (1<<CAN_IER_TMEIE_Pos);

/*Assign Global Pointer to function to empty function to avoid hardfault when not setting them with callbacks by upper layers*/
GLOB_CanDrvBusOffErrorCallback=EmptyFunction;
GLOB_CanDrvReceptionCallback=EmptyFunction;
GLOB_CanDrvTransmissionCallback=EmptyFunction;
GLOB_CanDrvWakeUpCallback=EmptyFunction;
}

/*______________________________________________________________________________________________________________*/

EnumCanDrvApiError enum_CanDrvSetBitTiming(u32_t baudrate, u32_t u32Clock)
{
/* Bit Timing Calculations 
   
   Given parameters: - CPU Clock                          (Given By User)
                     - BaudRate                           (Confiqured)
                     - Buadrate prescaler (BRP)           (Configured)
                     - Sampling point(%)                  (configured)

    Calculation Notes: 
    - Sync_segment = 1*tq
    - Bit Time = Sync_Segment + Bit Segment 1+ Bit Segment 2
    
    - CAN Clock         = CPU Clock/ BRP
    - Time quanta (tq)  = 1/CAN Clock

    - Bit Time        = 1/BaudRate
    - number of Time Quanta = bit time / Time Quanta
    - Bit Timing = Sync_Seg+Time Segment 1+ Time Segment 2
    - Sampling point (%) = (Sync_Seg+Time Segment 1) / Bit Time

      Additional Note:
    - Sync_Seg+ bit Segment 1+ bit Segment 2 = number of Time Quanta

  */

  /*check if Baudrate is out of range*/
  if(baudrate>CAN_MAX_BAUDRATE)
  {
    return CAN_API_NOT_OK;
  }

  else
  {

  /*caluclate Time Quanta*/
  float LOC_TimeQuanta=(BAUDRATE_PRESCALER/(float)u32Clock);

  /*get Bit Timing*/
  float  LOC_bitTiming=(1/(float)baudrate);

  /*calculate Bit Segment 1 (BS1)*/
    float   LOC_bitSegment1= ( (LOC_bitTiming*(SAMPLING_POINT/(float)100)) -LOC_TimeQuanta);
  /*calculate Bit Segment 2 (BS2)*/
    float  LOC_bitSegment2=LOC_bitTiming-LOC_bitSegment1;

  /*Calculate TS1 and TS2*/
  u8_t LOC_TS1Value= (u8_t )(LOC_bitSegment1/LOC_TimeQuanta);
  u8_t LOC_TS2Value= (u8_t )(LOC_bitSegment2/LOC_TimeQuanta);

  /*Configure BTR Register  */
  /*reset TS1 and TS2*/
    GLOB_strCanChannel->BTR &= ~ ((0x0F<<CAN_BTR_TS1_Pos) | (0x07<<CAN_BTR_TS2_Pos)) ;


  /*Set Values of TS1,TS2 and BRP in BTR */
  GLOB_strCanChannel->BTR |= ( (LOC_TS1Value-1) <<CAN_BTR_TS1_Pos)      |  
                             ( (LOC_TS2Value-1) <<CAN_BTR_TS2_Pos)      | 
                             ( (BAUDRATE_PRESCALER-1) <<CAN_BTR_BRP_Pos);
  /*set SJW value*/
  GLOB_strCanChannel->BTR &=~(1<<CAN_BTR_SJW_Pos);

  }
  return CAN_API_OK;
}

void vid_CanDrvStart(void)
{
    /*Clear Initalization Request bit  and sleep bit in CAN_MCR register to switch to normal mode*/
    GLOB_strCanChannel->MCR &=~( (1<<CAN_MCR_INRQ_Pos) | (1<<CAN_MCR_SLEEP_Pos) );
}

void vid_CanDrvStop(void)
{
    /*Set Initalization Request bit in CAN_MCR register to switch to initalization mode*/
     CREW_SET_BIT(GLOB_strCanChannel->MCR,CAN_MCR_INRQ_Pos);
}

/*______________________________________________________________________________________________________________*/

EnumCanDrvApiError enum_CanDrvTransmit(const strCanDrvFrameInfo *frame)
{
/*Check if Mailbox 0 is not empty*/
if(CREW_GET_BIT(GLOB_strCanChannel->TSR,CAN_TSR_TME0_Pos)!= MAILBOX_EMPTY)
{
    return CAN_API_NOT_OK;
}
/*else if empty*/
else
{

/************Assign frame ID depending on frame format*******/
/*Check if IDE is Standard or Extended*/
 if(frame->IDE==STANDARD_FORMAT)
 {
 /*check if Frame ID is within the 11 bit value or not*/
   if(frame->FrameID > MAX_STANDARD_ID_VALUE)
    {
    return CAN_API_NOT_OK;
    }

 /*else value is within 11 bit range*/
   else
    {
        /*Assign Frame ID in Mailbox 0 register*/
    GLOB_strCanChannel->sTxMailBox[0].TIR = (frame->FrameID <<CAN_TI0R_STID_Pos);

        /*Clear IDE bit for Standard Frame Format*/
    CREW_CLR_BIT(GLOB_strCanChannel->sTxMailBox[0].TIR,CAN_TI0R_IDE_Pos);
    
    }
}
    
 /*else if Format is Extended */
 else if (frame->IDE==EXTENDED_FORMAT)
 {

  /*validate Extended ID is within Valid Range (29 bits)*/
    if(frame->FrameID > MAX_EXTENDED_ID_VALUE)
    {
    return CAN_API_NOT_OK;
    }

  /*else value is in range*/
    else
    {
      /*Assign Frame ID in Mailbox 0 register*/
        GLOB_strCanChannel->sTxMailBox[0].TIR |= ( (frame->FrameID) << CAN_TI0R_EXID_Pos );

      /*Set IDE bit for Extended Frame Format*/
        CREW_SET_BIT(GLOB_strCanChannel->sTxMailBox[0].TIR,CAN_TI0R_IDE_Pos);
    }
 }

 /*else Format is not Standard or Extended Format*/
 else
 {
    return CAN_API_NOT_OK;
 }


/************Assign RTR depending on frame Type*********/
/*if RTR is data frame*/
 if(frame->RTR==DATA_FRAME)
 {
    CREW_CLR_BIT(GLOB_strCanChannel->sTxMailBox[0].TIR,CAN_TI0R_RTR_Pos);
 }

/*else RTR is Remote Frame*/
 else if(frame->RTR==REMOTE_FRAME)
 {
    CREW_SET_BIT(GLOB_strCanChannel->sTxMailBox[0].TIR,CAN_TI0R_RTR_Pos);
 }

/*else RTR is not Remote or Data Frame*/
 else
 {
     return CAN_API_NOT_OK;
 }

 /*****************Assign DLC Value*******************/
/*check if DLC is bigger than 8 bytes*/
if(frame->DLC > 8)
{
    return CAN_API_NOT_OK;
}
/*else DLC value is in range*/
else
{
  /*Clear DLC bit Field and set it to the frame DLC value*/
    GLOB_strCanChannel->sTxMailBox[0].TDTR&=~(0x0F<<0);
    GLOB_strCanChannel->sTxMailBox[0].TDTR|= (frame->DLC << CAN_TDT0R_DLC_Pos);
}

/*****************Set Data Values*******************/
/*Set the First 4 Bytes of Data in DATA low register*/
GLOB_strCanChannel->sTxMailBox[0].TDLR = (  (frame->data[3] << 24) | 
                              (frame->data[2] << 16) |
                              (frame->data[1] <<  8) | 
                              (frame->data[0]) );

/*Set the Last 4 Bytes of Data in DATA High register*/
GLOB_strCanChannel->sTxMailBox[0].TDHR = (  (frame->data[7] << 24) | 
                              (frame->data[6] << 16) |
                              (frame->data[5] <<  8) | 
                              (frame->data[4]) );

/*Request A Transmission Request*/
CREW_SET_BIT(GLOB_strCanChannel->sTxMailBox[0].TIR,CAN_TI0R_TXRQ_Pos);

}

return CAN_API_OK;
}

/*______________________________________________________________________________________________________________*/

void vid_CanRecieve(strCanDrvFrameInfo *frame)
 {
  /*Read Frame Format*/
  if (CREW_GET_BIT(GLOB_strCanChannel->sFIFOMailBox[0].RIR,CAN_RI0R_IDE_Pos)==STANDARD_FORMAT) {
    frame->IDE = STANDARD_FORMAT;
    frame->FrameID     = 0x000007FF & (GLOB_strCanChannel->sFIFOMailBox[0].RIR >> CAN_TI0R_STID_Pos);
  } else {
    frame->IDE = EXTENDED_FORMAT;
    frame->FrameID    = 0x1FFFFFFF & (GLOB_strCanChannel->sFIFOMailBox[0].RIR >>CAN_TI0R_EXID_Pos);
  }
  /* Read Frame Type        */
  if (CREW_GET_BIT(GLOB_strCanChannel->sFIFOMailBox[0].RIR,CAN_RI0R_RTR_Pos) == DATA_FRAME) {
    frame->RTR =   DATA_FRAME;
  } else {
    frame->RTR  = REMOTE_FRAME;
  }
  /* Read Data Length   */
  frame->DLC     = (GLOB_strCanChannel->sFIFOMailBox[0].RDTR) & 0x0F;

  /* Read data bytes              */
  frame->data[0] = (GLOB_strCanChannel->sFIFOMailBox[0].RDLR      ) & 0xFF;
  frame->data[1] = (GLOB_strCanChannel->sFIFOMailBox[0].RDLR >>  8) & 0xFF;
  frame->data[2] = (GLOB_strCanChannel->sFIFOMailBox[0].RDLR >> 16) & 0xFF;
  frame->data[3] = (GLOB_strCanChannel->sFIFOMailBox[0].RDLR >> 24) & 0xFF;

  frame->data[4] = (GLOB_strCanChannel->sFIFOMailBox[0].RDHR      ) & 0xFF;
  frame->data[5] = (GLOB_strCanChannel->sFIFOMailBox[0].RDHR >>  8) & 0xFF;
  frame->data[6] = (GLOB_strCanChannel->sFIFOMailBox[0].RDHR >> 16) & 0xFF;
  frame->data[7] = (GLOB_strCanChannel->sFIFOMailBox[0].RDHR >> 24) & 0xFF;

 /* Release FIFO 0 output mailbox */
  GLOB_strCanChannel->RF0R |= CAN_RF0R_RFOM0;             
 }

/*______________________________________________________________________________________________________________*/

EnumCanDrvApiError enum_SetAcceptenceFilter(u32_t id,u8_t format,u8_t filterNumber)
 {

   /*check if id and filters is valid*/
    if(filterNumber>CAN_FILTERS_TOTAL_NUM || ( id>MAX_STANDARD_ID_VALUE && format==STANDARD_FORMAT) || (id>MAX_EXTENDED_ID_VALUE && format==EXTENDED_FORMAT) )
    {
      return CAN_API_NOT_OK;
    }
  /*Set Filter Initalization bit*/
  CREW_SET_BIT(GLOB_strCanChannel->FMR,CAN_FMR_FINIT_Pos);

  /*Set the filter 0 to Identifier List mode*/
  CREW_SET_BIT(GLOB_strCanChannel->FM1R,filterNumber);

  /*Set Filter 0 to a single 32 bit sacle configuration*/
  CREW_SET_BIT(GLOB_strCanChannel->FS1R,filterNumber);

  /*Set Filter 0 Acceptance ID*/
  GLOB_strCanChannel->sFilterRegister[filterNumber].FR1 = (id<<21);

 /*Assign filter 0 passed msg to FIFO 0*/
  CREW_CLR_BIT(GLOB_strCanChannel->FFA1R,filterNumber);

  /*activate filter 0*/
  CREW_SET_BIT(GLOB_strCanChannel->FA1R,filterNumber);

  /*clear Filter initalization bit*/
  CREW_CLR_BIT(GLOB_strCanChannel->FMR,CAN_FMR_FINIT_Pos);

   return CAN_API_OK;
 }

/*______________________________________________________________________________________________________________*/

void enum_ClearAcceptenceFilter(u8_t filterNumber)
 {
  /*diactivate filter bank number*/
  CREW_CLR_BIT(GLOB_strCanChannel->FA1R,filterNumber);
 }

/*______________________________________________________________________________________________________________*/

void vid_CanLoopBacktestModeEnable (void) 
{ 
  GLOB_strCanChannel->BTR &= ~(CAN_BTR_SILM | CAN_BTR_LBKM);
  GLOB_strCanChannel->BTR |=   (1<<CAN_BTR_LBKM_Pos);
}

/*______________________________________________________________________________________________________________*/

void vid_CanSilenttestMode(void)
{
 GLOB_strCanChannel->BTR &= ~( CAN_BTR_LBKM | CAN_BTR_SILM);
GLOB_strCanChannel->BTR |=   (1<<CAN_BTR_SILM_Pos);
}

/*______________________________________________________________________________________________________________*/

void vid_CanSilentModeEnable (void) 
{ 
  GLOB_strCanChannel->BTR &= ~(CAN_BTR_SILM | CAN_BTR_LBKM);
  GLOB_strCanChannel->BTR |=  (1U<<CAN_BTR_SILM_Pos);
}

/*______________________________________________________________________________________________________________*/

void vid_CanDrvSetReceiveCallPack(void(*ptr_UserCallback)(void))
{
    if((ptr_UserCallback != NULLPTR) && (GLOB_CanDrvReceptionCallback == EmptyFunction)){
        GLOB_CanDrvReceptionCallback = ptr_UserCallback;
    }
}

/*______________________________________________________________________________________________________________*/

void vid_CanDrvSetTransmitCallPack(void(*ptr_UserCallback)(void))
{
    if((ptr_UserCallback != NULLPTR) && (GLOB_CanDrvTransmissionCallback == EmptyFunction)){
        GLOB_CanDrvTransmissionCallback = ptr_UserCallback;
    }
}

/*______________________________________________________________________________________________________________*/

void vid_CanDrvSetBusOffErrorCallback(void(*ptr_UserCallback)(void))
{
    if((ptr_UserCallback != NULLPTR) && (GLOB_CanDrvBusOffErrorCallback==EmptyFunction)){
        GLOB_CanDrvBusOffErrorCallback = ptr_UserCallback;
    }
}

/*______________________________________________________________________________________________________________*/

void vid_CanDrvSetIDWakeUp(u32_t CANID,void(*ptr_UserCallback)(void))
{   
  /*set callback function address to global variable*/
    if((ptr_UserCallback != NULLPTR) && (GLOB_CanDrvWakeUpCallback == EmptyFunction)){
        GLOB_CanDrvWakeUpCallback = ptr_UserCallback;
    }
    
    /*set wake up ID to global variable*/
    GLOB_WakeUpID=CANID;


}

/*______________________________________________________________________________________________________________*/

EnumCanDrvErrorType enum_CanDrvGetLastError(void)
{
  EnumCanDrvErrorType LOC_LastError=No_ERROR;

  /*extract last error code information from CAN_ESR register, type cast the extracted code into the defined enum (enum values match the codes defined in the datasheet)*/
  LOC_LastError= (EnumCanDrvErrorType) GLOB_strCanChannel->ESR & CAN_ESR_LEC_Msk;

  return LOC_LastError;
  
}

bool enum_isCanBusOff (void)
{
  return GET_BIT(GLOB_strCanChannel->ESR, CAN_ESR_BOFF_Pos);
}

/*________________________________IRQ Handlers Implementation _______________________________*/
/*______________________________________________________________________________________________________________*/

/* Interrupt to this handler is triggered when a CAN Frame is Received in FIFO 0*/
 void  USB_LP_CAN1_RX0_IRQHandler(void)
{   
  /*check if Global variable is not null*/
  if(GLOB_CanDrvReceptionCallback!=NULL)
  {
    /*call reception callback*/
    GLOB_CanDrvReceptionCallback();
  }

  /*extract the received CAN ID and check if the ID received is a wakeUp ID*/
  if( (0x000007FF & (GLOB_strCanChannel->sFIFOMailBox[0].RIR >> 21)) == GLOB_WakeUpID)
  {
     /*call the wakeUp Callback*/
     GLOB_CanDrvWakeUpCallback();
  }
 
 /*if not the wake Up ID*/
  else
  {
     /*do nothing*/
  }

}

/*______________________________________________________________________________________________________________*/

/* Interrupt to this handler is triggered when a Transmission of a frame in mailbox 0 is completed successfully
   Request Complete Mailbox zero should e cleared to enable a new transmission of any new upcoming farme  */
void  USB_HP_CAN1_TX_IRQHandler(void)
{
     /* if request completed for mailbox 0      */
     if (CAN1->TSR & CAN_TSR_RQCP0) 
     {  
      /* reset request complete bit  */
     CAN1->TSR |= CAN_TSR_RQCP0;    

     /*call successful Transmit indicator function by callback*/
     GLOB_CanDrvTransmissionCallback();
     } 

     else
     {
      /*do nothing*/
     }     
     
}

/*______________________________________________________________________________________________________________*/

void  CAN1_SCE_IRQHandler(void)
{
  /*check if ISR is entered due to bus off flag*/
  if(CREW_GET_BIT(GLOB_strCanChannel->ESR,CAN_ESR_BOFF_Pos) == TRUE)
  {
     /*call a callback function*/
     GLOB_CanDrvBusOffErrorCallback();
  }

  else 
  {
    /*do nothing*/
  }
}
