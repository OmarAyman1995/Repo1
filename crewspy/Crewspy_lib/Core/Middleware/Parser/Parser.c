#include "Parser.h"




/**
 * @brief extract service id from request frame and return it
 * 
 * @param buffer buffer that has service id
 * @return service id in buffer 
 */
uint8_t Parse_ServiceID(uint8_t const *buffer)
{
    uint8_t retval = 0;

    if(NULL == buffer)
    {
        retval = SERVICE_ERR;
    }
    else
    {
        retval = buffer[IDX_SERVICEID];
    }
    return retval;
}
