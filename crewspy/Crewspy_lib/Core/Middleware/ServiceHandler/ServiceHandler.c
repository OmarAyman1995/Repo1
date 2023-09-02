#include "ServiceHandler.h"

#define PRIVILEGE_FLAG_ONE           1

/*carries all services with their ids*/
volatile struct  function_mapping function_map[MAX_SERVICES_NUM];

/*counts number of servies registered in system*/
static volatile uint8_t num_services = 0;

/* Carries Last Executed Service*/
volatile uint8_t current_serviceid = 0;


/**
 * @brief saves service and assign id of it
 *
 * @param service_id id of service
 * @param ptr function address of the service
 * @todo(Mohamed Abdelaziz) check for reserved id
 */
void ServHndl_RegisterService(uint8_t service_id, function_ptr ptr)
{
    if (num_services < MAX_SERVICES_NUM)
    {
        /*Check if this id is already registered before*/
        for(uint8_t i = 0; i < num_services; (i++)){
            if(service_id == function_map[i].id){
                return;
            }
        }

        /*Register ID*/
        function_map[num_services].id = service_id;
        function_map[num_services].addr = ptr;
        (num_services++);
    }
}


/**
 * @brief call service by id
 *
 * @param service_id id of service
 */
void ServHndl_ExecuteService(uint8_t service_id)
{
    uint8_t i = 0;
    function_ptr ptr = NULL;
    for ((i = 0); i < num_services; (i++))
    {
        if (function_map[i].id == service_id)
        {
            ptr = function_map[i].addr;
            current_serviceid = service_id;
            ptr();
            return;
        }
    }
}


/**
 * @brief Make the Service privilege (execute after response)
 * 
 * @param id id of service
 */
void ServHndl_SetPrivilege(uint8_t id){
    uint8_t i = 0;

     for ((i = 0); i < num_services; (i++))
    {
        if (function_map[i].id == id)
        {
            function_map[i].privilege_flag = PRIVILEGE_FLAG_ONE;
            return;
        }
    }
}


/**
 * @brief Get Privilege Flag of Service
 * 
 * @param id id of service
 * @return privilege flag is either 0/1 
 */
uint8_t ServHndl_getPrivilege(uint8_t id){
    uint8_t i = 0;
    uint8_t retval = 0;
     for ((i = 0); i < num_services; (i++))
    {
        if (function_map[i].id == id)
        {
            retval = function_map[i].privilege_flag;
        }
    }
    return retval;
}


/**
 * @brief Get Last Executed Service
 * 
 * @return uint8_t 
 */
uint8_t ServHndl_GetCurrentService(void)
{
    return current_serviceid;
}
