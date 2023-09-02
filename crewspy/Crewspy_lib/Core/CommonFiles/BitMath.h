#ifndef __BITMATH_H
#define __BITMATH_H


/*READ MODIFY WRITE*/
#define SET_BIT(VAR,BIT_NO) (VAR |= 1UL<<BIT_NO)        /*SET_BIT set BIT_NO with HIGH in Variable*/
#define CLR_BIT(VAR,BIT_NO) (VAR &= ~(1UL<<BIT_NO))     /*Clear it set BIT_NO with LOW in Variable*/
#define TOGGLE_BIT(VAR,BIT_NO) (VAR ^= (1UL<<BIT_NO))   /*TOGGLE if BIT_NO is HIGH it set it to LOW and Vice Versa*/
#define ASSIGN_BIT(VAR,BIT_NO,VALUE)  (VAR=(VAR &(~(1UL<<BIT_NO))) | (VALUE<<BIT_NO))  //ASSIGHN BIT_NO in variable to HIGH or LOW*/
#define GET_BIT(VAR,BIT_NO)  ((VAR>>BIT_NO) & 0x01UL)   /*GET BIT_NO Value*/


#endif
