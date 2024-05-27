/**
 * @file PwmCommander.c
 *
 * @author     Omar Ayman (omar.ayman@crewteq.com)
 * @brief      source file of PwmCommander
 * @version    1.0.0
 * @date       2024-03-20
 *
 * @copyright  Copyright (crewteq.com) 2024
 */

/*__________________Includes_____________________________________*/
#include "PwmCommander.h"

/*____________________Public APIs___________________________________*/

/*____________________Public Variables___________________________________*/


/*____________________Privates___________________________________*/
/// @brief this is the array which contains 8 bits Header of the SAE1850 frame to send through OBD connector
PRIVATE enumBitsManagerHL_e enum_arrSAE1850Header[8] ;

/// @brief this is the array which contains 8 bytes Header of the SAE1850 frame to send through OBD connector
PRIVATE enumBitsManagerHL_e enum_arrSAE1850Data[64];

/// @brief this function is responsible for converting the OBD data coming 
///        from uppder layer to data type compatible with SAE1850 components (ones and zeros)
/// @param u8OBDdata the OBD data Coming from the Upper Layer   
PRIVATE void vid_SplitBitsFromOBDdata(const u8_t* u8OBDdata)
{
    /* ---- LOCALs ----*/
    u8_t LOC_u8NoOfBytes = 0 ;
    /* ---- Actions ---- */
    if(u8OBDdata!=NULL)
    {
        while(LOC_u8NoOfBytes<8)
        {
            for(u8_t LOC_u8Counter =0;LOC_u8Counter<8;LOC_u8Counter++)
            {
                if((u8OBDdata[LOC_u8NoOfBytes] & (1<<LOC_u8Counter)) == (1<<LOC_u8Counter))
                {
                    enum_arrSAE1850Data[(8*LOC_u8NoOfBytes)+LOC_u8Counter] = HIGH_BIT_BITS_MANAGER;
                }
                else 
                {
                    enum_arrSAE1850Data[(8*LOC_u8NoOfBytes)+LOC_u8Counter] = LOW_BIT_BITS_MANAGER;
                }   
            } 
            LOC_u8NoOfBytes++;        
        }   
    }
    
}
/*____________________Implementations___________________________________*/

enumRetPWMCommander_e enum_PwmCommanderCollectFrame(const u8_t* u8OBDdata)
{
    /* ----- LOCALs -----*/
    enumRetPWMCommander_e LOC_enumRetVal = UNKOWN_PWM_COMMANDER;

    /* ---- Actions -------*/
    if(u8OBDdata!=NULL)
    {
        /* HEADER */
        enum_arrSAE1850Header[HEADER_SAE1850_PRIORITY0] = 0 ;// highest priority
        enum_arrSAE1850Header[HEADER_SAE1850_PRIORITY1] = 0 ;// highest priority
        enum_arrSAE1850Header[HEADER_SAE1850_PRIORITY2] = 0 ;// highest priority
        
        enum_arrSAE1850Header[HEADER_SAE1850_H] = 0 ; //1 byte header 
        enum_arrSAE1850Header[HEADER_SAE1850_K] = 1 ; //NO IFS 
        enum_arrSAE1850Header[HEADER_SAE1850_Y] = 0 ; // Functional Addressing 

        enum_arrSAE1850Header[HEADER_SAE1850_Z1] = 0 ;//NOT Extended addressing
        enum_arrSAE1850Header[HEADER_SAE1850_Z0] = 0 ;//there is DATA in this message 

        /* DATA*/
        vid_SplitBitsFromOBDdata(u8OBDdata);

        /* CRC */

        /* EOD */
        
        LOC_enumRetVal = VALID_PWM_COMMANDER;
    }
    else 
    {
        LOC_enumRetVal = NOT_VALID_PWM_COMMANDER;
    }
    
    /*------- Return -------*/

    return LOC_enumRetVal ; 
}

enumRetPWMCommander_e enum_PwmCommanderSendFrame(void)
{
    /* ----- LOCALs -----*/
    enumRetPWMCommander_e LOC_enumRetVal = UNKOWN_PWM_COMMANDER;
    enumRetBitsManager_e  LOC_enumRetFromBitsMangAPIs = UNKOWN_BITS_MANAGER;
    /* ---- Actions -------*/

    /* SOF */
    LOC_enumRetFromBitsMangAPIs = enum_BitsManagerSendSOF();

    /* HEADER */
    if(LOC_enumRetFromBitsMangAPIs == VALID_BITS_MANAGER)
    {
        for(u8_t LOC_u8Counter =0 ;LOC_u8Counter<8;LOC_u8Counter++)
        {
            if(enum_arrSAE1850Header[LOC_u8Counter] == HIGH_BIT_BITS_MANAGER)
            {
                LOC_enumRetFromBitsMangAPIs = enum_BitsManagerSendHigh(1);
            } 
            else if(enum_arrSAE1850Header[LOC_u8Counter] == LOW_BIT_BITS_MANAGER)
            {
                LOC_enumRetFromBitsMangAPIs = enum_BitsManagerSendLow(1);
            } 
            else 
            {
                LOC_enumRetVal = NOT_VALID_PWM_COMMANDER;
            }
        } 
    }
    else 
    {
        LOC_enumRetVal = NOT_VALID_PWM_COMMANDER;
    }

    /* DATA */
    if(LOC_enumRetFromBitsMangAPIs == VALID_BITS_MANAGER)
    {
        for(u8_t LOC_u8Counter =0 ;LOC_u8Counter<64;LOC_u8Counter++)
        {
            if(enum_arrSAE1850Data[LOC_u8Counter] == HIGH_BIT_BITS_MANAGER)
            {
                LOC_enumRetFromBitsMangAPIs = enum_BitsManagerSendHigh(1);
            } 
            else if(enum_arrSAE1850Data[LOC_u8Counter] == LOW_BIT_BITS_MANAGER)
            {
                LOC_enumRetFromBitsMangAPIs = enum_BitsManagerSendLow(1);
            } 
            else 
            {
                LOC_enumRetVal = NOT_VALID_PWM_COMMANDER;
            }
        }
    } 
    else 
    {
        LOC_enumRetVal = NOT_VALID_PWM_COMMANDER;
    }
    
    /* CRC  (to be implemented)*/

    /* EOD */
    if(LOC_enumRetFromBitsMangAPIs == VALID_BITS_MANAGER)
    {
        LOC_enumRetFromBitsMangAPIs = enum_BitsManagerSendEOD();
        if(LOC_enumRetFromBitsMangAPIs != VALID_BITS_MANAGER)
        {
            LOC_enumRetVal = NOT_VALID_PWM_COMMANDER;
        }
    }
    else 
    {
        LOC_enumRetVal = NOT_VALID_PWM_COMMANDER;
    }
    
    /*------- Return -------*/

    return LOC_enumRetVal ; 
}

enumRetPWMCommander_e enum_PwmCommanderRecFrame(u8_t* ptr_u8RecFrame)
{
    /* ----- LOCALs ------*/
    enumRetPWMCommander_e LOC_enumRetVal = UNKOWN_PWM_COMMANDER;
    PRIVATE enumBitsManagerHL_e   LOC_arr_enumBitsRec [100];
    
    /// @brief this is the array which contains 8 bits Header of the SAE1850 frame to Receive from OBD connector
    PRIVATE enumBitsManagerHL_e enum_arrSAE1850HeaderRec[8] ;

    /// @brief this is the array which contains 8 bytes Header of the SAE1850 frame to Receive from OBD connector
    PRIVATE enumBitsManagerHL_e enum_arrSAE1850DataRec[64];
    /* ----- ACTIONs ------*/
    if(ptr_u8RecFrame!=NULL)
    {
        if(enum_BitsManagerGetBits(LOC_arr_enumBitsRec) == VALID_BITS_MANAGER)
        {
            LOC_enumRetVal = VALID_PWM_COMMANDER;
            /* SOF */
            if(LOC_arr_enumBitsRec[0] != SOF_BIT_BITS_MANAGER)
            {
            LOC_enumRetVal = NOT_VALID_PWM_COMMANDER;  
            }
            else 
            {
                /* HEADER */
                for(u8_t LOC_u8Counter=1; LOC_u8Counter<9; LOC_u8Counter++)
                {
                if(LOC_arr_enumBitsRec[LOC_u8Counter] == LOW_BIT_BITS_MANAGER)
                {
                        enum_arrSAE1850HeaderRec[LOC_u8Counter-1] = LOW_BIT_BITS_MANAGER;
                }
                else if(LOC_arr_enumBitsRec[LOC_u8Counter] == HIGH_BIT_BITS_MANAGER)
                {
                        enum_arrSAE1850HeaderRec[LOC_u8Counter-1] = HIGH_BIT_BITS_MANAGER;
                }
                else 
                {
                        LOC_enumRetVal = NOT_VALID_PWM_COMMANDER;  
                        break;
                }
                }
                /* DATA */
                for(u8_t LOC_u8Counter=9; LOC_u8Counter<73; LOC_u8Counter++)
                {
                    if(LOC_arr_enumBitsRec[LOC_u8Counter] == LOW_BIT_BITS_MANAGER)
                    {
                        enum_arrSAE1850DataRec[LOC_u8Counter-1] = LOW_BIT_BITS_MANAGER;
                    }
                    else if(LOC_arr_enumBitsRec[LOC_u8Counter] == HIGH_BIT_BITS_MANAGER)
                    {
                        enum_arrSAE1850DataRec[LOC_u8Counter-1] = HIGH_BIT_BITS_MANAGER;
                    }
                    else 
                    {
                            LOC_enumRetVal = NOT_VALID_PWM_COMMANDER;  
                            break;
                    }
                }
                /* CRC (to be implemented)*/
                /* EOD (wait low for 200 us)  (to be implemented)*/   
            }
            /*filling the response*/
            if(LOC_enumRetVal == VALID_PWM_COMMANDER)
            {
                for(u8_t LOC_u8Counter=0; LOC_u8Counter<64; LOC_u8Counter++)
                {
                    ptr_u8RecFrame[LOC_u8Counter] =(u8_t)enum_arrSAE1850DataRec[LOC_u8Counter+8];
                }
            }     
        }
        else 
        {
            LOC_enumRetVal = NOT_VALID_PWM_COMMANDER;
        }       

    }
    else 
    {
        LOC_enumRetVal = NOT_VALID_PWM_COMMANDER;
    }
    /*------ Return ------*/
    return LOC_enumRetVal;
}

