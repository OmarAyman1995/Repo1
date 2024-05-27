#ifndef __VEHICLE_APP_H
#define __VEHICLE_APP_H

#include "typedefs.h"
#include "services.h"
#include "ComM.h"
#include "OfferedServices.h"
#include "VehicleDataTypes.h"



#define FUEL_SYSTEM_STATUS_TIME 5 // 150ms

#define VEHICLE_ENABLE_SETUP_MODE 1
#define VEHICLE_ENABLE_SCHEDULING_EVENTS 1


/**
 * @brief Initialize the vehicle application
 * @note CCO-CDD-227 CCO-CDD-200
 * 
 * @return 1 if success, 0 if fail
 */
void vid_VehicleApp_Init(void);


/**
 * @brief the periodic function of vehicle application
 * @note CCO-CDD-201 CCO-CDD-202 CCO-CDD-203 CCO-CDD-204 CCO-CDD-205 CCO-CDD-206 CCO-CDD-207 CCO-CDD-208
 *       CCO-CDD-209 CCO-CDD-210 CCO-CDD-211 CCO-CDD-212 CCO-CDD-213 CCO-CDD-214 CCO-CDD-215
 */
void vid_VehicleApp_Manage(void);


/**
 * @brief makes vehicle request
 * 
 * @param request request object that contains all information needed about that request
 * @return VehicleApp_StatusTypeDef stateus of the Request API
 * @note CCO-CDD-201 CCO-CDD-202 CCO-CDD-203 CCO-CDD-204 CCO-CDD-205 CCO-CDD-206 CCO-CDD-207 CCO-CDD-208 CCO-CDD-209 CCO-CDD-210
         CCO-CDD-211 CCO-CDD-212 CCO-CDD-213 CCO-CDD-214 CCO-CDD-215 CCO-CDD-216 CCO-CDD-217 CCO-CDD-218 CCO-CDD-219 CCO-CDD-221
 */
VehicleApp_StatusTypeDef enum_VehicleApp_Request(Vehicle_RequestTypedef *request);


/**
 * @brief gets the system fuel state to monitor the motor state on or off
 * 
 * @return uint8_t motor state 1 on, 0 off
 */
u8_t u8_VehicleApp_getMotorState(void);






#endif
