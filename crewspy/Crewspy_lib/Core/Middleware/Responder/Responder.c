#include "Responder.h"
#include "COM_Adapter.h"
#include "Address.h"
#include "UserInterface.h"

#define IDX_SERVICEID   0
#define IDX_PARAMS      1

/* Storage of Target Configurations (CPUID)*/
uint8_t TargetConfig[IDS_SIZE] = {0};



static void StoreServiceID(uint8_t *buffer, uint8_t service_id);

static void StoreParameters(uint8_t *buffer,
                                 uint8_t *params,
                                 size_t sizeOfParams);


/**
 * @brief store service id in buffer
 *
 * @param buffer pointer to desired buffer
 * @param service_id desired ID to store
 */
static void StoreServiceID(uint8_t *buffer, uint8_t service_id)
{
    buffer[IDX_SERVICEID] = service_id;
}


/**
 * @brief store paramters in buffer
 *
 * @param buffer pointer to desired buffer
 * @param params  pointer desired parameters to store
 */
static void StoreParameters(uint8_t *buffer,
                            uint8_t *params,
                            size_t sizeOfParams)
{
    uint8_t i = 0;

    for((i = 0); (i < sizeOfParams); (i++))
    {
        buffer[IDX_PARAMS + i] = params[i];
    }
}


/**
 * @brief takes buffer and fill it with service id and parameters
 * 
 * @param buffer pointer to desired buffer
 * @param service_id service id to be stored in the buffer
 * @param params pointer to parameters to be stored in the buffer
 * @param sizeOfParams size of the parameters
 */
void Responder_PutServiceIDAndParams(uint8_t *buffer,
                   uint8_t service_id,
                   uint8_t * params,
                   size_t sizeOfParams)
{
    if((NULL == buffer)  || (NULL == params))
    {
        /*forced negative response*/
    }
    else
    {
        /* Store service id and parameters in the buffer */
        StoreServiceID(buffer,service_id);
        StoreParameters(buffer,params,sizeOfParams);
    }

}


/**
 * @brief Sends CPUID of the target to Com Protocol
 * 
 */
void Responder_SendTargetConfigs(void)
{

    /* Access Hardware and Store CPUID in a buffer */
    TargetConfig[0] = DEVICEID_CPUID_SERIVCE;
    TargetConfig[1] = (uint8_t)(CPUID_REG >> 4);
    TargetConfig[2] = (uint8_t)(((CPUID_REG >> 4) >> 8) & MASKING_DEVICDEID_CPUID);
    
    /* Send the buffer to Communication */
    ComAdapterSendBuffer(TargetConfig, POSITIVE_RESPONSE, IDS_SIZE );
}