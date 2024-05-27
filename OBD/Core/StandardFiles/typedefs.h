#ifndef __TYPEDEFS_H_
#define __TYPEDEFS_H_
/**
 * @brief These #define statements create type-safe aliases for the standard integer,float and double types
 *
 */
typedef   unsigned char     	               u8_t;
typedef   signed char     	                   i8_t;
typedef   unsigned short int                   u16_t;
typedef   signed short int                     itn16_t;
typedef   unsigned long int 	               u32_t;
typedef   unsigned long long                   u64_t;
typedef   signed long int 	                   i32_t;
typedef   float             	               float32_t;
typedef   double            	               double64_t;

#define BUFFER_SIZE 20



#define FREERTOS    1


/**
 * @brief simple typedef for a pointer to a function that takes no arguments and returns no value
 *
 */
typedef void (*pFunction)(void);
typedef void (*MqttCallback)(u8_t *message, u32_t size);
typedef float32_t (*pToFuncUint)(u8_t*);
typedef void (*pToFuncCallbackStaticService)(u8_t, u8_t*,u32_t,u8_t);
typedef void (*ResponseCallback)(u8_t* ,u32_t, u8_t );
typedef u8_t (*ConvUnitType)(u8_t A, u8_t B, u8_t C, u8_t D, u8_t* output_string);

/**
 * @brief common definitions for TRUE and FALSE
 *
 */
#define TRUE                                    1
#define FALSE                                   0


/**
 * @brief define error codes for a program
 *
 */
#define ERROR_SUCCESS                           0
#define ERROR_INVALID_PARAM                     1
#define ERROR_TIMEOUT                           2
#define ERROR_OTHER                             3

/**
 * @brief defining of null datatypes
 *
 */
#define NULLPTR (void *)0
#define NULLINT 0
#define NULLFLOAT 0.0


#define PUBLIC extern
#define PRIVATE static

#define IDENTICAL 0U

#define ON 1
#define OFF 0
#define bool u8_t

/* - - - - - - Configurations - - - - - - */
#define UT OFF
#endif /* TYPEDEFS_H_ */
