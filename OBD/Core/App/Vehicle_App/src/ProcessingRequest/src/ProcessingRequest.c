#include "ProcessingRequest.h"
#include "string.h"
#include "OBDIIHandler.h"
#include "JsonLibrary.h"


PRIVATE JsonString GLOB_strResponseObject = {0};

/**
 * @brief collects the response of dynamic pids or static pids in a json buffer
 * 
 * @param pid the response of which pid
 * @param data_field response datafield
 * @param data_size size of the response
 * @param notification notification about whether to collect that response in my buffer (GLOB_arrResponseBuffer) or send it (static/dynamic request is completed)
 */
PRIVATE void vid_callbackOfStaticOrDynamicRequests(u8_t pid, u8_t* data_field, u32_t data_size, u8_t notification){
    u8_t conversionCheck = 0;
    u8_t dataConverted[50] = {0};

    if(notification == NOTIFICATION_COLLET_BUFFER){
          // collect in buffer
          conversionCheck = u8_ConvertOBDToPhysicalValue(pid,
                                                         data_field[A_INDEX],
                                                         data_field[B_INDEX],
                                                         data_field[C_INDEX],
                                                         data_field[D_INDEX],
                                                         dataConverted);

        if(conversionCheck == 1){
          JsonAdd(&GLOB_strResponseObject, &pid, dataConverted, 1);
        }else{
          JsonAdd(&GLOB_strResponseObject, &pid, "PID CE", 1);
        }

      }else if (notification == NOTIFICATION_ERROR){
        // error happened in CAN
        JsonAdd(&GLOB_strResponseObject, &pid, "PID NE", 1);
      }
      else if (notification == NOTIFICATION_NOT_SUPPORTED){
        // not supported
        JsonAdd(&GLOB_strResponseObject, &pid, "PID NS", 1);

      }else if (notification == NOTIFICATION_COLLECT_VIN){
        // collect vin
        JsonAdd(&GLOB_strResponseObject, "VIN", data_field, 0);
      }else{
        // notification send
          JsonStringfy(&GLOB_strResponseObject);
      }
}





u8_t u8_Process_Request(RequestType LOC_enum_Service, Vehicle_RequestTypedef *LOC_str_request){

    u8_t LOC_u8_requestStatus = 0;
    u8_t LOC_u8_mode = 0;
    u8_t LOC_u8_pid = 0;
    OBDResponse_s OBDIIResponse = {0};

    // check arguments
    if((LOC_str_request == NULLPTR) && (LOC_enum_Service == MANUAL_REQUEST)){
        return 0;
    }

    // check range of OBD Mode and OBD Pid
    if((LOC_enum_Service == MANUAL_REQUEST) && ((LOC_str_request->obd_mode > OBD_MODE_10) || (LOC_str_request->obd_pid > MAX_PIDS))){
        return 2;
    }

    switch (LOC_enum_Service)
    {
        case MANUAL_REQUEST:
          LOC_u8_mode = LOC_str_request->obd_mode;
          LOC_u8_pid = LOC_str_request->obd_pid;
          LOC_u8_requestStatus = u8_MakeManualOBDRequest(LOC_u8_mode, LOC_u8_pid);


          if(LOC_u8_requestStatus == 1){

              OBDIIReceiveResponse(&OBDIIResponse);
              // convert only if mode is 1 (show current data)
              if(LOC_u8_mode == 1){
              
                  u8_ConvertOBDToPhysicalValue(OBDIIResponse.Pid,
                                               OBDIIResponse.Buffer[A_INDEX],
                                               OBDIIResponse.Buffer[B_INDEX],
                                               OBDIIResponse.Buffer[C_INDEX],
                                               OBDIIResponse.Buffer[D_INDEX],
                                               GLOB_strResponseObject.Buffer);

                  GLOB_strResponseObject.size = u32_getConvertedSize();
              }else{
                  GLOB_strResponseObject.size = OBDIIResponse.Length;
                  cpy_array(GLOB_strResponseObject.Buffer, OBDIIResponse.Buffer, OBDIIResponse.Length);
              }
          }else{
            // request failed

          }
        break;

        case DYNAMIC_DATA_REQUEST:
          JsonInit(&GLOB_strResponseObject);
          vid_dynamicRequest(vid_callbackOfStaticOrDynamicRequests);
          LOC_u8_requestStatus = 1;
        break;

        case STATIC_DATA_REQUEST:
          JsonInit(&GLOB_strResponseObject);
          vid_staticRequest(vid_callbackOfStaticOrDynamicRequests);
          LOC_u8_requestStatus = 1;
        break;

        case UPDATE_SUPPORT_TYPE_REQUEST:
          LOC_u8_requestStatus = u8_update_pids_database();
        break;

    default:
        LOC_u8_requestStatus = 2; // unknown service
        break;
    }

    
    return LOC_u8_requestStatus;
}

u8_t* p_getResponseMessage(void){
    return GLOB_strResponseObject.Buffer;
}

u32_t u32_getResponseSize(void){
    return GLOB_strResponseObject.size;
}

void vid_Processing_Reset(void){
    JsonReset(&GLOB_strResponseObject);
}
